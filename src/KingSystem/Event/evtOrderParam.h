#pragma once

#include <basis/seadTypes.h>
#include <codec/seadHashCRC32.h>
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys::evt {

enum class OrderParamType : u16 {
    Invalid = 0,
    Int = 1,
    Float = 2,
    String = 3,
    Bool = 4,
    Actor = 5,
    Array = 6,
};

struct OrderParamEntry {
    void clear() {
        hash = 0;
        size = 0;
        type = OrderParamType::Invalid;
        name = nullptr;
        data = nullptr;
    }

    u32 hash;
    sead::SafeString* name;
    void* data;
    u32 size;
    OrderParamType type;
};

class OrderParam {
public:
    explicit OrderParam(sead::Heap* heap);
    OrderParam(const OrderParam& other) { *this = other; }
    virtual ~OrderParam();
    OrderParam& operator=(const OrderParam& other);
    bool initialize(s32 entry_count);
    void uninitialize();

    const OrderParamEntry* getParam(s32 index) const;
    bool addParamInt(s32 val, const sead::SafeString& name);
    bool addParamFloat(f32 val, const sead::SafeString& name);
    bool addParamString(const sead::SafeString& val, const sead::SafeString& name);
    bool addParamBool(bool val, const sead::SafeString& name);
    bool addParamActor(ksys::act::BaseProc* actor, sead::SafeString& name);
    bool addParamArray(char* array, u32 size, sead::SafeString& name);

    OrderParamEntry* tryAlloc(OrderParamType type, u32 size, const sead::SafeString& name);
    bool getIntByName(const sead::SafeString& name, u32** out_ptr) const;
    bool getStringByName(const sead::SafeString& name, sead::SafeString** out_ptr) const;
    bool getArrayByName(const sead::SafeString& name, void** out_ptr, u32* out_size) const;

private:
    bool doAssign(const OrderParam& other);

    OrderParamEntry* getFreeEntry();
    void* getPointerByName(const sead::SafeString& name, OrderParamType type,
                           u32* out_size = nullptr) const;

    template <typename T>
    bool getPointerByName(const sead::SafeString& name, T** out_ptr, OrderParamType type,
                          u32* out_size = nullptr) const {
        auto* ptr = getPointerByName(name, type, out_size);
        if (!ptr)
            return false;
        *out_ptr = static_cast<T*>(ptr);
        return true;
    }

    template <typename T>
    T* tryAllocParam(const sead::SafeString& name, OrderParamType type, u32 size = 0) {
        auto* ptr = getPointerByName(name, type);
        if (ptr)
            return nullptr;

        auto* entry = tryAlloc(type, size, name);
        if (!entry || !entry->data)
            return nullptr;
        return static_cast<T*>(entry->data);
    }

    sead::Heap* mHeap;
    sead::Buffer<OrderParamEntry> mEntries;
    u32 mEntryCount = 0;
    bool mInitialized = false;
};
}  // namespace ksys::evt
