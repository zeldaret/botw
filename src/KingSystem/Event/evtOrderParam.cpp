#include "KingSystem/Event/evtOrderParam.h"
#include <basis/seadTypes.h>
#include <codec/seadHashCRC32.h>
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::evt {

OrderParam::OrderParam(sead::ExpHeap* heap) {
    mHeap = heap;
}

OrderParam::~OrderParam() {
    uninitialize();
}

bool OrderParam::initialize(s32 entry_count) {
    sead::FixedSafeString<0x100> error_message;

    error_message.format("[%s] initialize(%d) is failed.", "ksys::evt::OrderParam", entry_count);
    uninitialize();
    if (entry_count == 0)
        return true;
    if (!mHeap)
        return false;
    if (entry_count < 1)
        return false;
    if (!mEntries.tryAllocBuffer(entry_count, mHeap))
        return false;

    // I think compiler is unrolling this loop
    for (s32 i = 0; i != mEntries.size(); ++i) {
        clearEntry(&mEntries[i]);
    }
    mEntryCount = 0;
    mInitialized = true;
    return true;
}

void OrderParam::uninitialize() {
    for (s32 i = 0; i < mEntries.size(); i++) {
        auto* e = &mEntries[i];
        auto* name_ptr = e->mName;
        if (name_ptr)
            delete (sead::FixedSafeString<0x20>*)name_ptr;
        auto* ptr = e->mPointer;
        if (ptr) {
            switch (e->mType) {
            case OrderParamType::STRING:
                delete (sead::FixedSafeString<0x40>*)ptr;
                break;
            case OrderParamType::INT:
            case OrderParamType::INT_2:
                delete (u32*)ptr;
                break;
            case OrderParamType::BYTE:
                delete (char*)ptr;
                break;
            case OrderParamType::ACTOR:
                delete (ksys::act::BaseProcLink*)ptr;
                break;
            case OrderParamType::ARRAY:
                mHeap->free(ptr);
                break;
            default:
                break;
            }
        }
        clearEntry(e);
    }
    mEntries.freeBuffer();
    mEntryCount = 0;
    mInitialized = false;
}

const OrderParamEntry* OrderParam::getParam(const s32 index) const {
    sead::FixedSafeString<0x100> error_message;

    error_message.format("[%s] getParam(%d) is failed.", "ksys::evt::OrderParam", index);
    if ((u32)std::max(0, mEntries.size()) > (u32)index) {
        return &mEntries[index];
    } else {
        return nullptr;
    }
}
OrderParam* OrderParam::assign(OrderParam* other) {
    if (this != other) {
        doAssign(other);
    }
    return this;
}

bool OrderParam::doAssign(OrderParam* other) {
    if (this == other)
        return true;
    if (!initialize(std::max(0, other->mEntries.size())))
        return false;
    for (s32 i = 0; i < mEntries.size(); i++) {
        auto* other_entry = other->getParam(i);
        if (other_entry) {
            auto* other_ptr = other_entry->mPointer;
            auto* other_name = other_entry->mName;
            ksys::act::BaseProcLink* link_ptr;
            ksys::act::BaseProc* actor_ptr;
            if (other_ptr && other_name) {
                switch (other_entry->mType) {
                case OrderParamType::INT:
                    if (!addParamInt(*static_cast<s32*>(other_ptr), *other_name))
                        return false;
                    break;
                case OrderParamType::INT_2:
                    if (!addParamInt2(*static_cast<s32*>(other_ptr), *other_name))
                        return false;
                    break;
                case OrderParamType::STRING:
                    if (!addParamString(*static_cast<sead::SafeString*>(other_ptr), *other_name))
                        return false;
                    break;
                case OrderParamType::BYTE:
                    if (!addParamByte(*static_cast<char*>(other_ptr), *other_name))
                        return false;
                    break;
                case OrderParamType::ACTOR:
                    link_ptr = static_cast<ksys::act::BaseProcLink*>(other_ptr);
                    actor_ptr =
                        sead::DynamicCast<ksys::act::BaseProc>(link_ptr->getProc(nullptr, nullptr));
                    if (!addParamActor(actor_ptr, *other_name))
                        return false;
                    break;
                case OrderParamType::ARRAY:
                    if (!addParamArray(static_cast<char*>(other_ptr), other_entry->mSize,
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
    auto* entry_ptr = tryAllocParam<s32>(name, OrderParamType::INT);
    if (!entry_ptr)
        return false;
    *entry_ptr = val;
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamInt2(s32 val, const sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<s32>(name, OrderParamType::INT_2);
    if (!entry_ptr)
        return false;
    *entry_ptr = val;
    ++mEntryCount;
    return true;
}
bool OrderParam::addParamString(const sead::SafeString& val, const sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<sead::BufferedSafeString>(name, OrderParamType::STRING);
    if (!entry_ptr)
        return false;
    entry_ptr->copy(val);
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamByte(char val, const sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<char>(name, OrderParamType::BYTE);
    if (!entry_ptr)
        return false;
    *entry_ptr = val;
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamActor(ksys::act::BaseProc* actor, sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<ksys::act::BaseProcLink>(name, OrderParamType::ACTOR);
    if (!entry_ptr)
        return false;
    if (!entry_ptr->acquire(actor, false))
        return false;
    ++mEntryCount;
    return true;
}

bool OrderParam::addParamArray(char* array, u32 size, sead::SafeString& name) {
    auto* entry_ptr = tryAllocParam<ksys::act::BaseProcLink>(name, OrderParamType::ARRAY, size);
    if (!entry_ptr)
        return false;
    std::memcpy(entry_ptr, array, size);
    ++mEntryCount;
    return true;
}

bool OrderParam::getIntByName(const sead::SafeString& name, u32** out_ptr) {
    return getPointerByName(name, out_ptr, OrderParamType::INT);
}

bool OrderParam::getStringByName(const sead::SafeString& name, sead::SafeString** out_ptr) {
    return getPointerByName(name, out_ptr, OrderParamType::STRING);
}

bool OrderParam::getArrayByName(const sead::SafeString& name, void** out_ptr, u32* out_size) {
    return getPointerByName(name, out_ptr, OrderParamType::ARRAY, out_size);
}

// This one also does not match
OrderParamEntry* OrderParam::tryAlloc(OrderParamType type, u32 size, const sead::SafeString& name) {
    sead::FixedSafeString<0x100> error_message;

    error_message.format("[%s] tryAlloc_(%d, %d, %s) is failed.", "ksys::evt::OrderParam", type,
                         size, name.cstr());

    for (s32 i = 0; i < mEntries.size(); i++) {
        auto* e = &mEntries[i];

        if (!e->mPointer) {
            void** in_ptr = &(e->mPointer);
            std::nothrow_t nothrow_t;
            auto* heap = mHeap;
            if (!heap)
                return nullptr;

            e->mName = new (heap, nothrow_t) sead::FixedSafeString<0x20>(name);
            switch (type) {
            case OrderParamType::STRING:
                *in_ptr = new (heap, nothrow_t) sead::FixedSafeString<0x40>;
                size = sizeof(sead::FixedSafeString<0x40>);
                break;
            case OrderParamType::INT:
            case OrderParamType::INT_2:
                *in_ptr = new (heap, nothrow_t) u32(0);
                size = sizeof(u32);
                break;

            case OrderParamType::BYTE:
                *in_ptr = new (heap, nothrow_t) char(0);
                size = sizeof(char);
                break;
            case OrderParamType::ACTOR:
                *in_ptr = new (heap, nothrow_t) ksys::act::BaseProcLink;
                size = sizeof(ksys::act::BaseProcLink);
                break;
            case OrderParamType::ARRAY:
                *in_ptr = new (heap, nothrow_t) char[size];
            default:
                break;
            }
            e->mSize = size;
            if (e->mPointer) {
                e->mHash = sead::HashCRC32::calcStringHash(e->mName->cstr());
                e->mType = type;
                return e;
            }
            if (e->mName)
                delete e->mName;
            // clearEntry(e);
            *e = {};
            return nullptr;
            // auto* entry = mAllocArray+i;
            // if (*in_ptr) {

            //} else {

            //}
        }
    }

    return nullptr;
}

// OrderParamEntry* OrderParam::getEntryByName(const sead::SafeString& name, OrderParamType type) {
//     const u32 hash = sead::HashCRC32::calcStringHash(name);
//     for (s32 i = 0; i < mEntries.size(); i++) {
//         if (mEntries[i].mHash == hash && mEntries[i].mType == type) {
//             return &mEntries[i];
//         }
//     }
//     return nullptr;
// }

void* OrderParam::getPointerByName(const sead::SafeString& name, OrderParamType type,
                                   u32* out_size) const {
    const u32 hash = sead::HashCRC32::calcStringHash(name);
    for (s32 i = 0; i < mEntries.size(); i++) {
        if (mEntries[i].mHash == hash && mEntries[i].mType == type) {
            if (out_size)
                *out_size = mEntries[i].mSize;
            return mEntries[i].mPointer;
        }
    }
    return nullptr;
}

}  // namespace ksys::evt
