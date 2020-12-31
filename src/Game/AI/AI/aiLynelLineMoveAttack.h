#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelLineMoveAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelLineMoveAttack, ksys::act::ai::Ai)
public:
    explicit LynelLineMoveAttack(const InitArg& arg);
    ~LynelLineMoveAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mGoalRadius_s{};
    // dynamic_param at offset 0x48
    bool* mIsSkipPrepare_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetVel_d{};
};

}  // namespace uking::ai
