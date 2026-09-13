#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFindHorseRideTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFindHorseRideTarget, ksys::act::ai::Ai)
public:
    explicit EnemyFindHorseRideTarget(const InitArg& arg);
    ~EnemyFindHorseRideTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mSurpriseAttackPer_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const int* mLostTimer_s{};
    // static_param at offset 0x50
    const int* mChaseTime_s{};
    // static_param at offset 0x58
    const float* mSurpriseAttackRange_s{};
    // static_param at offset 0x60
    const float* mAttackRange_s{};
    // static_param at offset 0x68
    const float* mAttackVMin_s{};
    // static_param at offset 0x70
    const float* mAttackVMax_s{};
    // static_param at offset 0x78
    const float* mLostVMin_s{};
    // static_param at offset 0x80
    const float* mLostVMax_s{};
    // static_param at offset 0x88
    const float* mLostRange_s{};
    // static_param at offset 0x90
    const float* mAttackTargetSpeed_s{};
    // static_param at offset 0x98
    const float* mReChaseDist_s{};
};

}  // namespace uking::ai
