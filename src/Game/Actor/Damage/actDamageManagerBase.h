#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "Game/Actor/Damage/actDamageInfoMgr.h"
#include "Game/Actor/Damage/actStruct20.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actIDamageManager.h"

namespace ksys {
class Message;
}  // namespace ksys

namespace ksys::act {
class Actor;
class ActorParam;
}  // namespace ksys::act

namespace uking::act {

// FIXME: Unknown base 2. Helper functions maybe? Might also contain some of the fields from
// DamageManagerBase.
class DamageManagerBase_UnknownBase2 {
public:
    virtual ~DamageManagerBase_UnknownBase2() = default;
};

class DamageManagerBase : public ksys::act::IDamageManager, public DamageManagerBase_UnknownBase2 {
public:
    explicit DamageManagerBase(ksys::act::Actor* actor);
    ~DamageManagerBase() override = default;

    SEAD_RTTI_OVERRIDE(DamageManagerBase, ksys::act::IDamageManager)

    u32 getDamage() override;
    s32 getField48() override { return mField_48; }
    s32 getMinDmg() override { return mMinDmg; }
    s32 getField50() override { return mField_50; }
    s32 getField54() override { return mField_54; }
    bool checkDamageFlags() override { return false; }
    s32 getFlags2() override { return mFlags2; }
    virtual f32 getStasisBlowPowerRatio() { return 0.0f; }
    virtual bool getStasisBlowVelocity(sead::Vector3f* velocity) { return false; }
    virtual bool applyDamage(s32& life);
    virtual bool handleMessage(const ksys::Message&) { return false; }
    virtual void accumulateStasisBlowVelocity() {}
    virtual s32 getNumCallbacks();
    virtual bool initCallbacks(sead::Heap* heap);

    // m20 (FIXME: incomplete)
    virtual void resetDamage();

    virtual void preDelete2() {}
    virtual void calcDamage() {}
    virtual bool allocStruct20(sead::Heap* heap);
    virtual void preDelete1();
    virtual s64 m25() { return 0; }
    virtual s64 m26() { return 0; }
    virtual s32 getPosition() { return 0; }
    virtual bool getDamageDir(sead::Vector3f* dir) { return false; }

    //(FIXME: incomplete)
    virtual s64 m29(s64 a2);

    // qword pointer? (FIXME: incomplete)
    virtual s64 m30(u64 a2);

    virtual bool getHitDirection(sead::Vector3f* dir) { return false; }
    virtual s32 getDamageImpulse() { return 0; }
    virtual s64 getAttackOtherMaterialMask() { return 0; }
    virtual s64 tgSensorMaterialOnHitMaybe() { return 0; }
    virtual bool getAttackSourceMtx(sead::Matrix34f* mtx) { return false; }

    // FIXME: incomplete. Return dummy Base Proc Link
    virtual ksys::act::BaseProcLink* getAttacker();

    // FIXME: incomplete. Same as getAttacker, but return different Actor ProcLink I assume.
    virtual s64 m37();

    virtual s32 isDamageSourceObjectMaybe() { return 0; }

    // FIXME: Incomplete. Call isSlowTimeMaybe
    virtual bool isSlowTime();

    virtual s32 getAttackDirType() { return 0; }
    virtual s32 getAttackInfoFlagFC() { return 0; }
    virtual s32 isDamageItemFlagCheckDisabled() { return 0; }
    virtual void applyAttackInfoStateChangeDamage() {}
    virtual bool canTakeDamage();
    virtual void applyRequestedDamage() {}
    virtual void handleDamageForPlayer(u32* a2, u32* a3, u32* a4, u32* a5, u32* a6);
    virtual bool addDamage(s64 a2, s32 damage, s32 df48, s32 minDmg, s32 f50, s32 f54, s32 f40);
    virtual void onApplyDamage() {}

    virtual s32 getDamageFromTypeIndex(s32 damageTypeMaybe);

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

}  // namespace uking::act
