#pragma once

#include "Game/AI/Action/actionJumpToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AttackJumpToTarget : public JumpToTarget {
    SEAD_RTTI_OVERRIDE(AttackJumpToTarget, JumpToTarget)
public:
    explicit AttackJumpToTarget(const InitArg& arg);
    ~AttackJumpToTarget() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const int* mWeaponIdx_s{};
    // static_param at offset 0xd8
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0xe0
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0xe8
    const float* mJustAvoidAngle_s{};
    // static_param at offset 0xf0
    const bool* mIsIgnoreSmallHit_s{};
    // static_param at offset 0xf8
    const float* mPosOffsetDist_s{};
    // static_param at offset 0x100
    const bool* mIsCheckNoChangeAS_s{};
};

}  // namespace uking::action
