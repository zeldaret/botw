#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StepDoubleAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StepDoubleAttack, ksys::act::ai::Action)
public:
    explicit StepDoubleAttack(const InitArg& arg);
    ~StepDoubleAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mCloseDist_s{};
    // static_param at offset 0x30
    const float* mSpeed_s{};
    // static_param at offset 0x38
    const float* mRotSpd_s{};
    // static_param at offset 0x40
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x48
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x50
    const float* mJustAvoidAngle_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
