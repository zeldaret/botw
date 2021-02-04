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

    bool addParamInt(s32 val, const sead::SafeString& key);
    void addParamActor(ksys::act::BaseProc& actor, sead::SafeString& name);
    OrderParamEntry* tryAlloc(OrderParamType type, u32 size, sead::SafeString& name);
    bool getIntByName(const sead::SafeString& name, u32** out_ptr);
    bool getStringByName(const sead::SafeString& name, sead::SafeString** out_ptr);
    bool getArrayByName(const sead::SafeString& name, void** out_ptr, u32* out_size);

private:
    void* getPointerByName(const sead::SafeString& name, u32* out_size, OrderParamType type) const;

    template <typename T>
    bool getPointerByName(const sead::SafeString& name, T** out_ptr, u32* out_size,
                          OrderParamType type) const {
        auto* ptr = getPointerByName(name, out_size, type);
        if (!ptr)
            return false;
        *out_ptr = static_cast<T*>(ptr);
        return true;
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
