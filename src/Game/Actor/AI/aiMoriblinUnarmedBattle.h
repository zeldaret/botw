#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoriblinUnarmedBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoriblinUnarmedBattle, ksys::act::ai::Ai)
public:
    explicit MoriblinUnarmedBattle(const InitArg& arg);
    ~MoriblinUnarmedBattle() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFarDist_s{};
    // static_param at offset 0x40
    const float* mOutDist_s{};
    // static_param at offset 0x48
    const float* mBaseDist_s{};
    // static_param at offset 0x50
    const int* mWeaponIdx_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x60
    const float* mAttackStartRotate_s{};
    // static_param at offset 0x68
    const float* mAttackIntervalIntensity_s{};
    // static_param at offset 0x70
    const int* mPursuingAttackInterval_s{};
    // static_param at offset 0x78
    const float* mPursuingAttackStartAng_s{};
};

}  // namespace uking::ai
