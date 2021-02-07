#include "KingSystem/Event/evtOrderParam.h"
#include <codec/seadHashCRC32.h>
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::evt {

OrderParam::OrderParam(sead::Heap* heap) {
    mHeap = heap;
}

OrderParam::~OrderParam() {
    uninitialize();
}

bool OrderParam::initialize(s32 entry_count) {
    sead::FixedSafeString<0x100> error_message;

    error_message.format("[%s] initialize(%d) is failed.", "ksys::evt::OrderParam", entry_count);
    uninitialize();
    if (!entry_count)
        return true;
    if (!mHeap)
        return false;
    if (!mEntries.tryAllocBuffer(entry_count, mHeap))
        return false;

    for (u32 i = 0; i < u32(entry_count); i++)
        mEntries[i].clear();

    mEntryCount = 0;
    mInitialized = true;
    return true;
}

void OrderParam::uninitialize() {
    for (s32 i = 0; i < mEntries.size(); i++) {
        auto& entry = mEntries[i];
        if (entry.name)
            delete (entry.name);
        auto* ptr = entry.data;
        if (ptr) {
            switch (entry.type) {
            case OrderParamType::String:
                delete static_cast<sead::SafeString*>(ptr);
                break;
            case OrderParamType::Int:
                delete static_cast<s32*>(ptr);
                break;
            case OrderParamType::Float:
                delete static_cast<f32*>(ptr);
                break;
            case OrderParamType::Bool:
                delete static_cast<bool*>(ptr);
                break;
            case OrderParamType::Actor:
                delete static_cast<act::BaseProcLink*>(ptr);
                break;
            case OrderParamType::Array:
                mHeap->free(ptr);
                break;
            default:
                break;
            }
        }
        entry.clear();
    }
    mEntries.freeBuffer();
    mEntryCount = 0;
    mInitialized = false;
}

const OrderParamEntry* OrderParam::getParam(const s32 index) const {
    sead::FixedSafeString<0x100> error_message;

    error_message.format("[%s] getParam(%d) is failed.", "ksys::evt::OrderParam", index);
    if (u32(std::max(0, mEntries.size())) > u32(index)) {
        return &mEntries[index];
    } else {
        return nullptr;
    }
}

OrderParam& OrderParam::operator=(const OrderParam& other) {
    if (this != &other) {
        doAssign(other);
    }
    return *this;
}

bool OrderParam::doAssign(const OrderParam& other) {
    if (this == &other)
        return true;

    if (!initialize(std::max(0, other.mEntries.size())))
        return false;
    for (s32 i = 0; i < mEntries.size(); i++) {
        auto* other_entry = other.getParam(i);
        if (other_entry) {
            auto* other_ptr = other_entry->data;
            auto* other_name = other_entry->name;
            ksys::act::BaseProcLink* link_ptr;
            ksys::act::BaseProc* actor_ptr;
            if (other_ptr && other_name) {
                switch (other_entry->type) {
                case OrderParamType::Int:
                    if (!addParamInt(*static_cast<s32*>(other_ptr), *other_name))
                        return false;
                    break;
                case OrderParamType::Float:
                    if (!addParamFloat(*static_cast<f32*>(other_ptr), *other_name))
                        return false;
                    break;
                case OrderParamType::String:
                    if (!addParamString(*static_cast<sead::SafeString*>(other_ptr), *other_name))
                        return false;
                    break;
                case OrderParamType::Bool:
                    if (!addParamBool(*static_cast<bool*>(other_ptr), *other_name))
                        return false;
                    break;
                case OrderParamType::Actor:
                    link_ptr = static_cast<ksys::act::BaseProcLink*>(other_ptr);
                    actor_ptr =
                        sead::DynamicCast<ksys::act::BaseProc>(link_ptr->getProc(nullptr, nullptr));
                    if (!addParamActor(actor_ptr, *other_name))
                        return false;
                    break;
                case OrderParamType::Array:
                    if (!addParamArray(static_cast<char*>(other_ptr), other_entry->size,
                                       *other_name))
                        return false;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return true;
}

bool OrderParam::addParamInt(s32 val, const sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<s32>(name, OrderParamType::Int);
    if (!entry_ptr)
        return false;
    *entry_ptr = val;
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamFloat(f32 val, const sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<f32>(name, OrderParamType::Float);
    if (!entry_ptr)
        return false;
    *entry_ptr = val;
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamString(const sead::SafeString& val, const sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<sead::BufferedSafeString>(name, OrderParamType::String);
    if (!entry_ptr)
        return false;
    entry_ptr->copy(val);
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamBool(bool val, const sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<bool>(name, OrderParamType::Bool);
    if (!entry_ptr)
        return false;
    *entry_ptr = val;
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamActor(ksys::act::BaseProc* actor, sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<ksys::act::BaseProcLink>(name, OrderParamType::Actor);
    if (!entry_ptr)
        return false;
    if (!entry_ptr->acquire(actor, false))
        return false;
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamArray(char* array, u32 size, sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<char>(name, OrderParamType::Array, size);
    if (!entry_ptr)
        return false;
    std::memcpy(entry_ptr, array, size);
    ++mEntryCount;
    return true;
}

bool OrderParam::getIntByName(const sead::SafeString& name, u32** out_ptr) const {
    return getPointerByName(name, out_ptr, OrderParamType::Int);
}

bool OrderParam::getStringByName(const sead::SafeString& name, sead::SafeString** out_ptr) const {
    return getPointerByName(name, out_ptr, OrderParamType::String);
}

bool OrderParam::getArrayByName(const sead::SafeString& name, void** out_ptr, u32* out_size) const {
    return getPointerByName(name, out_ptr, OrderParamType::Array, out_size);
}

OrderParamEntry* OrderParam::getFreeEntry() {
    for (s32 i = 0; i < mEntries.size(); i++) {
        auto* entry = &mEntries[i];
        if (!entry->data) {
            return entry;
        }
    }
    return nullptr;
}

OrderParamEntry* OrderParam::tryAlloc(OrderParamType type, u32 size, const sead::SafeString& name) {
    sead::FixedSafeString<0x100> error_message;

    error_message.format("[%s] tryAlloc_(%d, %d, %s) is failed.", "ksys::evt::OrderParam",
                         static_cast<u16>(type), size, name.cstr());

    OrderParamEntry* entry = getFreeEntry();

    if (!entry)
        return nullptr;
    auto* heap = mHeap;
    if (!heap)
        return nullptr;

    entry->name = new (heap, std::nothrow_t()) sead::FixedSafeString<0x20>(name);

    switch (type) {
    case OrderParamType::Int:
        entry->data = new (heap, std::nothrow_t()) s32();
        entry->size = sizeof(s32);
        break;
    case OrderParamType::Float:
        entry->data = new (heap, std::nothrow_t()) f32();
        entry->size = sizeof(f32);
        break;
    case OrderParamType::String:
        entry->data = new (heap, std::nothrow_t()) sead::FixedSafeString<0x40>;
        entry->size = sizeof(sead::FixedSafeString<0x40>);
        break;
    case OrderParamType::Bool:
        entry->data = new (heap, std::nothrow_t()) bool();
        entry->size = sizeof(bool);
        break;
    case OrderParamType::Actor:
        entry->data = new (heap, std::nothrow_t()) ksys::act::BaseProcLink;
        entry->size = sizeof(act::BaseProcLink);
        break;
    case OrderParamType::Array:
        entry->data = new (heap, std::nothrow_t()) char[size];
        entry->size = size;
        break;
    default:
        break;
    }

    auto* ptr = entry->data;

    if (ptr) {
        entry->hash = sead::HashCRC32::calcStringHash(*entry->name);
        entry->type = type;
        return entry;
    }

    if (entry->name)
        delete entry->name;
    entry->clear();
    return nullptr;
}

void* OrderParam::getPointerByName(const sead::SafeString& name, OrderParamType type,
                                   u32* out_size) const {
    const u32 hash = sead::HashCRC32::calcStringHash(name);
    for (s32 i = 0; i < mEntries.size(); i++) {
        if (mEntries[i].hash == hash && mEntries[i].type == type) {
            if (out_size)
                *out_size = mEntries[i].size;
            return mEntries[i].data;
        }
    }
    return nullptr;
}

}  // namespace ksys::evt
