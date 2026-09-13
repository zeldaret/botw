#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoiseTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoiseTarget, ksys::act::ai::Ai)
public:
    explicit EnemyNoiseTarget(const InitArg& arg);
    ~EnemyNoiseTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mIsTrgChangeUnderWaterState_a{};
    // static_param at offset 0x40
    const int* mLostTime_s{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const int* mRerouteTimeMin_s{};
    // static_param at offset 0x58
    const int* mRerouteTimeMax_s{};
    // static_param at offset 0x60
    const float* mNearDist_s{};
    // static_param at offset 0x68
    const float* mFarDist_s{};
    // static_param at offset 0x70
    const int* mShieldIdx_s{};
    // static_param at offset 0x78
    const float* mSearchShieldDist_s{};
    // static_param at offset 0x80
    const int* mNoShieldEquipWpIdx_s{};
    // static_param at offset 0x88
    const float* mNoShieldSearchDist_s{};
    // static_param at offset 0x90
    const float* mUnReachableToRepathDist_s{};
    // static_param at offset 0x98
    const float* mTooFarPathDist_s{};
};

}  // namespace uking::ai
