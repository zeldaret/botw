#pragma once

#include <basis/seadTypes.h>
#include <codec/seadHashCRC32.h>
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys::evt {

enum class OrderParamType : u16 {
    INVALID = 0,
    INT = 1,
    INT_2 = 2,
    STRING = 3,
    BYTE = 4,
    ACTOR = 5,
    ARRAY = 6

};

struct OrderParamEntry {
    u32 mHash = 0;
    // u32 _4; alignment gap
    sead::SafeString* mName = nullptr;
    void* mPointer = nullptr;  //_10
    u32 mSize = 0;             //_18
    OrderParamType mType = OrderParamType::INVALID;
    // u16 _1e; alignment gap
};

class OrderParam {
    OrderParam(sead::ExpHeap* mHeap);
    virtual ~OrderParam();

public:
    bool initialize(s32 entry_count);
    void uninitialize();
    OrderParam* assign(OrderParam* other);

    inline const OrderParamEntry* getParam(const s32 index) const;
    bool addParamInt(s32 val, const sead::SafeString& name);
    bool addParamInt2(s32 val, const sead::SafeString& name);
    bool addParamString(const sead::SafeString& val, const sead::SafeString& name);
    bool addParamByte(char val, const sead::SafeString& name);
    bool addParamActor(ksys::act::BaseProc* actor, sead::SafeString& name);
    bool addParamArray(char* array, u32 size, sead::SafeString& name);

    OrderParamEntry* tryAlloc(OrderParamType type, u32 size, const sead::SafeString& name);
    bool getIntByName(const sead::SafeString& name, u32** out_ptr);
    bool getStringByName(const sead::SafeString& name, sead::SafeString** out_ptr);
    bool getArrayByName(const sead::SafeString& name, void** out_ptr, u32* out_size);

private:
    bool doAssign(OrderParam* other);
    // OrderParamEntry* getEntryByName(const sead::SafeString& name, OrderParamType type);
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
        if (!entry || !(entry->mPointer))
            return nullptr;
        return static_cast<T*>(entry->mPointer);
    }

    inline void clearEntry(OrderParamEntry* e) {
        e->mHash = 0;
        e->mSize = 0;
        e->mType = OrderParamType::INVALID;
        e->mName = nullptr;
        e->mPointer = nullptr;
    }
    sead::ExpHeap* mHeap;
    sead::Buffer<OrderParamEntry> mEntries;
    u32 mEntryCount = 0;
    bool mInitialized = false;
};
}  // namespace ksys::evt
