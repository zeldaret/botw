#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LargeAttack : public ActionEx {
    SEAD_RTTI_OVERRIDE(LargeAttack, ActionEx)
public:
    explicit LargeAttack(const InitArg& arg);
    ~LargeAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x38
    const float* mAttackRatio_s{};
    // static_param at offset 0x40
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x48
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x50
    const float* mJustAvoidAngle_s{};
};

}  // namespace uking::action
