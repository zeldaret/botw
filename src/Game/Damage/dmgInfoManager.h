#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <thread/seadReadWriteLock.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Resource/resHandle.h"

namespace uking::dmg {

// FIXME: incomplete
class DamageInfoMgr {
    SEAD_SINGLETON_DISPOSER(DamageInfoMgr);
    DamageInfoMgr();
    virtual ~DamageInfoMgr();

public:
    // FIXME: incomplete
    class DamageItem {
    public:
        s32 mField_0;  // unknown
        sead::SafeArray<u8, 3> mCanTakeDamageFromType;
    };

    /// Boomerang remote bombs are a scrapped feature.
    static bool enableBoomerangRemoteBombs();
    static int getShieldRideBaseFrame();
    static int getShieldRideHitBaseDamage();
    static f32 getCriticalAttackRatio();

    bool isTrueFormMasterSword() const;

    sead::Buffer<DamageItem>& getDamagesArray() { return mDamagesArray; }
    const sead::Buffer<DamageItem>& getDamagesArray() const { return mDamagesArray; }
    f32 getMasterSwordSearchEvilDist() const { return mMasterSwordSearchEvilDist; }
    bool isMasterSwordDetectedEvil() const { return mMasterSwordDetectedEvil; }
    bool isMasterSwordDisableTrueForm() const { return mMasterSwordDisableTrueForm; }
    bool isOneHitObliteratorActive() const { return mOneHitObliteratorActive; }

private:
    /* 0x0028 */ u8 TEMP_8[0x5d0 - 0x28];
    /* 0x05d0 */ ksys::res::Handle mReactionTable;
    /* 0x0620 */ sead::Buffer<DamageItem> mDamagesArray;
    /* 0x0630 */ u8 TEMP_630[0xd00 - 0x630];
    /* 0x0d00 */ sead::ReadWriteLock mLock;
    /* 0x0db8 */ u8 TEMP_db8[0x11e4 - 0xdb8];
    /* 0x11e4 */ f32 mMasterSwordSearchEvilDist;
    /* 0x11e8 */ bool mMasterSwordDetectedEvil;
    /* 0x11e9 */ bool mMasterSwordDisableTrueForm;
    /* 0x11ea */ bool mOneHitObliteratorActive;
    /* 0x11f0 */ ksys::act::BaseProcLink _11f0;
    /* 0x1200 */ ksys::act::BaseProcLink _1200;
    /* 0x1210 */ ksys::act::BaseProcLink _1210;
    /* 0x1220 */ ksys::act::BaseProcLink _1230;
    /* 0x1230 */ sead::ReadWriteLock mProcLinkLock;
    /* 0x12e8 */ void* _12e8;
};
KSYS_CHECK_SIZE_NX150(DamageInfoMgr, 0x12F0);

}  // namespace uking::dmg
