#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class JumpAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(JumpAttack, ksys::act::ai::Action)
public:
    explicit JumpAttack(const InitArg& arg);
    ~JumpAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const float* mJumpHeight_s{};
    // static_param at offset 0x40
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x48
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x50
    const float* mJustAvoidAngle_s{};
    // static_param at offset 0x58
    const bool* mIsForceGuardBreak_s{};
};

}  // namespace uking::action
