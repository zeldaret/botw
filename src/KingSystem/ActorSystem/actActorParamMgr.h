#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

namespace res {
class GParamList;
}

namespace act {

// FIXME: incomplete
class ActorParam__Data_ {
public:
    u8 TEMP1[0xA0];

    ksys::res::GParamList* gParamList;
    u8 TEMP2[0x18];
    void* mDamageParam;
    u8 TEMP3[0x128];
};
KSYS_CHECK_SIZE_NX150(ActorParam__Data_, 0x1F0);

// FIXME: incomplete
class ActorParam__Data : public ActorParam__Data_ {
public:
    virtual void TEMP_VTABLE();  // vtable is still unknown

    u64 TEMP;  // Unknown number of fields(2+)
};
KSYS_CHECK_SIZE_NX150(ActorParam__Data, 0x200);

// FIXME: incomplete
class ActorParamMgr {
    SEAD_SINGLETON_DISPOSER(ActorParamMgr)
public:
    void init(sead::Heap* heap, sead::Heap* debug_heap);

    res::GParamList* getDummyGParamList() const;
};

}  // namespace act

}  // namespace ksys
