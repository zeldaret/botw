#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::act {

class Actor;
class IDamageManager;

class DamageCallback {
public:
    virtual ~DamageCallback() {}
    virtual void call(u32* a1, s32* a2, u32* a3, u32* a4, u32* a5, u64 a6);

    DamageCallback* mPrev;
    DamageCallback* mNext;
    IDamageManager* mDamageManager;
    u32 mEventId;
};

class Struct20Base {
    SEAD_RTTI_BASE(Struct20Base)

public:
    virtual ~Struct20Base() = default;

    virtual void reset();
    virtual void combineMaybe(Struct20Base* other);
};

class IDamageManager {
public:
    explicit IDamageManager(Actor* actor) : mActor(actor) {}

    SEAD_RTTI_BASE(IDamageManager)

    virtual ~IDamageManager() = default;

    virtual u32 getDamage() = 0;
    virtual s32 getField48() = 0;
    virtual s32 getMinDmg() = 0;
    virtual s32 getField50() = 0;
    virtual s32 getField54() = 0;
    virtual bool checkDamageFlags() = 0;
    virtual s32 getFlags2() = 0;
    virtual void addDamageCallback(s32 eventId, DamageCallback* callback);
    virtual void removeDamageCallback(DamageCallback* callback);

    // Sturct20 for Damage receive/send?
    Struct20Base* mStruct20_a = nullptr;
    Struct20Base* mStruct20_b = nullptr;

    Actor* mActor = nullptr;

    sead::Buffer<DamageCallback*> mCallbacks{};

    // Callback status flags?
    s32 mField_30 = 0;
    s8 mField_34 = 0;
};

}  // namespace ksys::act
