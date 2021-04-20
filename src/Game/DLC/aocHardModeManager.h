#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace uking::aoc {

class HardModeManager final {
    SEAD_SINGLETON_DISPOSER(HardModeManager)

    HardModeManager();
    virtual ~HardModeManager();

public:
    SEAD_ENUM(HardModeChange, IsLastPlayHardMode = 0, NerfHpRestore = 1, _2 = 2,
              DisableNoDeathDamage = 3, PatchGanonStunLock = 4, EnableLifeRegen = 5,
              RandomizeGuardianChargeBeam = 6, ApplyDamageMultiplier = 7,
              EnableShorterEnemyNotice = 8);
    SEAD_ENUM(Flag, EnableHardMode = 0);
    SEAD_ENUM(MultiplierType, HpRestore = 0, _1 = 1, EnemyNoticeDuration = 2)

    void init(sead::Heap* heap);

    void loadIsLastPlayHardModeFlag();
    void loadIsHardModeFlag();

    void storeIsLastPlayHardModeFlag();
    void resetIsLastPlayHardModeFlag();

    void calc();

    void nerfHpRestore(f32* hp) const;
    void nerfHpRestore(s32* hp) const;
    void modifyEnemyNoticeDuration(f32* value) const;

    static bool
    shouldApplyMasterModeDamageMultiplier(const ksys::act::ActorConstDataAccess& accessor);
    static void buffDamage(s32& damage);

    bool isTestOfStrengthShrine() const;

    bool rankUpEnemy(const sead::SafeString& actor_name, const ksys::map::Object& obj,
                     const char** new_name);

    void setHardModeChange(HardModeChange flag, bool on) { mHardModeChanges.changeBit(flag, on); }
    bool isHardModeChangeOn(HardModeChange flag) const { return mHardModeChanges.isOnBit(flag); }

    void setFlag(Flag flag, bool on) { mFlags.changeBit(flag, on); }
    bool checkFlag(Flag flag) const { return mFlags.isOnBit(flag); }

    f32 getMultiplier(MultiplierType type) const { return mMultipliers[type]; }

private:
    void setHardModeEnabledFlag(ksys::gdt::Manager::ResetEvent* event = nullptr);
    void initFlagHandles(ksys::gdt::Manager::ReinitEvent* event = nullptr);
    void init_();

    sead::BitFlag32 mHardModeChanges;
    sead::BitFlag32 mFlags;
    sead::SafeArray<f32, 3> mMultipliers;
    ksys::gdt::Manager::ResetSignal::Slot mGdtResetSlot;
    ksys::gdt::Manager::ReinitSignal::Slot mGdtReinitSlot;
    void* _120 = nullptr;
    ksys::res::Handle mFileHandle;
    ksys::gdt::FlagHandle mHardModeHighScoreFlag = ksys::gdt::InvalidHandle;
    ksys::gdt::FlagHandle mAoCHardModeEnabledFlag = ksys::gdt::InvalidHandle;
    ksys::gdt::FlagHandle mIsLastPlayHardModeFlag = ksys::gdt::InvalidHandle;
    sead::FixedSafeString<256> mMapType;
    sead::FixedSafeString<256> mMapName;
};
KSYS_CHECK_SIZE_NX150(HardModeManager, 0x3b8);

}  // namespace uking::aoc
