#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "Game/Damage/dmgInfoManager.h"
#include "Game/Damage/dmgStruct20.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class Actor;
class ActorParam;
}  // namespace ksys::act

namespace uking::dmg {

class DamageCallback;

// FIXME: Unknown base. This base seems to handle callbacks and messaging, so maybe a shared base?
class DamageManagerBase_UnknownBase1 {
public:
    explicit DamageManagerBase_UnknownBase1(ksys::act::Actor* WeaponActor);
    virtual ~DamageManagerBase_UnknownBase1() = default;

    // Sturct20 for Damage receive/send?
    Struct20Base* mStruct20_a = nullptr;
    Struct20Base* mStruct20_b = nullptr;

    ksys::act::Actor* mActor = nullptr;

    sead::Buffer<DamageCallback*> mCallbacks{};

    // Callback status flags?
    s32 mField_30 = 0;
    s8 mField_34 = 0;
};

// FIXME: Unknown base 2. Helper functions maybe? Might also contain some of the fields from
// DamageManagerBase.
class DamageManagerBase_UnknownBase2 {
public:
    virtual ~DamageManagerBase_UnknownBase2() = default;
};

class DamageManagerBase : public DamageManagerBase_UnknownBase1,
                          public DamageManagerBase_UnknownBase2 {
public:
    explicit DamageManagerBase(ksys::act::Actor* actor);
    ~DamageManagerBase() override = default;

    SEAD_RTTI_BASE(DamageManagerBase)

    virtual u32 getDamage();
    virtual s32 getField48() { return mField_48; }
    virtual s32 getMinDmg() { return mMinDmg; }
    virtual s32 getField50() { return mField_50; }
    virtual s32 getField54() { return mField_54; }
    virtual bool checkDamageFlags() { return false; }
    virtual s32 getFlags2() { return mFlags2; }
    virtual void addDamageCallback(s32 eventId, DamageCallback* callback);
    virtual void removeDamageCallback(DamageCallback* callback);
    virtual f32 m13() { return 0.0f; }
    virtual bool m14() { return false; }
    virtual bool applyDamage(s32& life);
    virtual bool m16() { return false; }
    virtual void m17() {}
    virtual s32 getNumCallbacks();
    virtual bool initCallbacks(sead::Heap* heap);

    // m20 (FIXME: incomplete)
    virtual void resetDamage();

    virtual void preDelete2() {}
    virtual void m22() {}
    virtual bool allocStruct20(sead::Heap* heap);
    virtual void preDelete1();
    virtual s64 m25() { return 0; }
    virtual s64 m26() { return 0; }
    virtual s32 getPosition() { return 0; }
    virtual s32 m28() { return 0; }

    //(FIXME: incomplete)
    virtual s64 m29(s64 a2);

    // qword pointer? (FIXME: incomplete)
    virtual s64 m30(u64 a2);

    virtual s32 m31() { return 0; }
    virtual s32 m32() { return 0; }
    virtual s64 m33() { return 0; }
    virtual s64 tgSensorMaterialOnHitMaybe() { return 0; }
    virtual s32 m35() { return 0; }

    // FIXME: incomplete. Return dummy Base Proc Link
    virtual ksys::act::BaseProcLink* getAttacker();

    // FIXME: incomplete. Same as getAttacker, but return different Actor ProcLink I assume.
    virtual s64 m37();

    virtual s32 m38() { return 0; }

    // FIXME: Incomplete. Call isSlowTimeMaybe
    virtual bool isSlowTime();

    virtual s32 m40() { return 0; }
    virtual s32 m41() { return 0; }
    virtual s32 m42() { return 0; }
    virtual void m43() {}
    virtual bool canTakeDamage();
    virtual void m45() {}
    virtual void handleDamageForPlayer(u32* a2, u32* a3, u32* a4, u32* a5, u32* a6);
    virtual bool addDamage(s64 a2, s32 damage, s32 df48, s32 minDmg, s32 f50, s32 f54, s32 f40);
    virtual void onApplyDamage() {}

    // Something depending on damage type?
    virtual s32 m49(s32 damageTypeMaybe);

    void clearCallbacks();
    void resetStuff();
    void callDamageCallbacks(u32 a2, u32* a3, s32* a4, u32* a5, u32* a6, u32* a7, u64 a8);
    s64 calcMaybe();

    inline void tryBuffDamage(s32& damage);
    inline void tryApplyDamageRecovery(s32& damage);

private:
    s32 mField_40 = 0;
    s32 mDamage = 0;
    s32 mField_48 = 0;
    s32 mMinDmg = 0;
    s32 mField_50 = -1;
    s32 mField_54 = -1;
    s32 mFlags2 = 0;
    s32 mDamageType = 0;
    s32 mDamageReactionTableStuff = -1;
    u8 mField_64 = 0;
    bool mIsOwnedByPlayer;
};
KSYS_CHECK_SIZE_NX150(DamageManagerBase, 0x68);

}  // namespace uking::dmg
