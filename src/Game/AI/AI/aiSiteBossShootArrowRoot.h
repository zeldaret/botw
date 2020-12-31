#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossShootArrowRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossShootArrowRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossShootArrowRoot(const InitArg& arg);
    ~SiteBossShootArrowRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mChildDeviceMax_s{};
    // static_param at offset 0x40
    const int* mChildDeviceSupplyNum_s{};
    // static_param at offset 0x48
    const int* mChildDeviceSupplyInterval_s{};
    // static_param at offset 0x50
    const int* mAtMinDamage_s{};
    // static_param at offset 0x58
    const int* mArrowRainBaseDamage_s{};
    // static_param at offset 0x60
    const int* mArrowRainAddDamage_s{};
    // static_param at offset 0x68
    const int* mAvoidCountMax_s{};
    // static_param at offset 0x70
    const int* mSeqAvoidRate_s{};
    // static_param at offset 0x78
    const int* mUpDownAvoidRate_s{};
    // static_param at offset 0x80
    const float* mPatternShiftFirstLifeRate_s{};
    // static_param at offset 0x88
    const float* mPatternShiftSecondLifeRate_s{};
    // static_param at offset 0x90
    const float* mPatternShiftThirdLifeRate_s{};
    // static_param at offset 0x98
    const float* mCancelCreateTornadoHeight_s{};
    // static_param at offset 0xa0
    const float* mAvoidAngle_s{};
    // static_param at offset 0xa8
    const float* mAvoidLifeRate_s{};
    // static_param at offset 0xb0
    const float* mAvoidDist_s{};
    // static_param at offset 0xb8
    const float* mAvoidDistRand_s{};
    // static_param at offset 0xc0
    const float* mAvoidWaitCount_s{};
    // static_param at offset 0xc8
    const float* mAvoidWaitCountRand_s{};
    // static_param at offset 0xd0
    const float* mTornadoCreateHeight_s{};
    // static_param at offset 0xd8
    sead::SafeString mNoWaitWarpAttackKey_s{};
    // static_param at offset 0xe8
    const sead::Vector3f* mChaseDist_s{};
    // static_param at offset 0xf0
    const sead::Vector3f* mChaseDistOffset_s{};
    // dynamic_param at offset 0xf8
    bool* mIsAttackPatternFixed_d{};
    // dynamic_param at offset 0x100
    bool* mIsCancelAttack_d{};
    // dynamic_param at offset 0x108
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
