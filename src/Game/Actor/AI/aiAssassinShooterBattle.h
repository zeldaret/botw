#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinShooterBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AssassinShooterBattle, ksys::act::ai::Ai)
public:
    explicit AssassinShooterBattle(const InitArg& arg);
    ~AssassinShooterBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mTiredTime_s{};
    // static_param at offset 0x48
    const float* mWarpDistNear_s{};
    // static_param at offset 0x50
    const float* mWarpDistFar_s{};
    // static_param at offset 0x58
    const float* mTerritoryDist_s{};
    // static_param at offset 0x60
    const float* mTiredGrHeight_s{};
    // static_param at offset 0x68
    const float* mIntervalIntensity_s{};
};

}  // namespace uking::ai
