#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

namespace res {
class GParamList;
}

namespace act {

// FIXME: incomplete
class ActorParam {
public:
    // FIXME: incomplete
    struct Data {
    public:
        u8 TEMP1[0xA0];

        res::GParamList* mGParamList;
        u8 TEMP2[0x18];
        void* mDamageParam;
        u8 TEMP3[0x128];
    };
    KSYS_CHECK_SIZE_NX150(ActorParam::Data, 0x1F0);

    // vtable is still unknown
    virtual void TEMP_VTABLE();

    u64 TEMP;  // Unknown number of fields(2+)
    Data mData;
};
KSYS_CHECK_SIZE_NX150(ActorParam, 0x200);

// FIXME: incomplete
class ActorParamMgr {
    SEAD_SINGLETON_DISPOSER(ActorParamMgr)
public:
    void init(sead::Heap* heap, sead::Heap* debug_heap);

    res::GParamList* getDummyGParamList() const;
};

}  // namespace act

}  // namespace ksys
