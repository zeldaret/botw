#pragma once

#include <basis/seadTypes.h>

namespace uking::dmg {

class DamageManagerBase;

// FIXME: incomplete
class DamageCallback {
public:
    virtual ~DamageCallback() {}
    virtual void call(u32* a1, s32* a2, u32* a3, u32* a4, u32* a5, u64 a6);

    DamageCallback* mPrev;
    DamageCallback* mNext;
    DamageManagerBase* mDamageManager;  // Might be a different base class(Interface?)
    u32 mEventId;
};

}  // namespace uking::dmg
