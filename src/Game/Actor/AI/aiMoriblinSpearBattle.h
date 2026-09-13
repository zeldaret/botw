#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoriblinSpearBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoriblinSpearBattle, ksys::act::ai::Ai)
public:
    explicit MoriblinSpearBattle(const InitArg& arg);
    ~MoriblinSpearBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFarDist_s{};
    // static_param at offset 0x40
    const float* mOutDist_s{};
    // static_param at offset 0x48
    const float* mNearDist_s{};
    // static_param at offset 0x50
    const float* mBaseDist_s{};
    // static_param at offset 0x58
    const int* mWeaponIdx_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x68
    const float* mAttackStartRotate_s{};
    // static_param at offset 0x70
    const float* mForceAttackDist_s{};
    // static_param at offset 0x78
    const float* mAttackIntervalIntensity_s{};
};

}  // namespace uking::ai
