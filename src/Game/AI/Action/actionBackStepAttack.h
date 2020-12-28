#pragma once

#include "Game/AI/Action/actionBackStepBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackStepAttack : public BackStepBase {
    SEAD_RTTI_OVERRIDE(BackStepAttack, BackStepBase)
public:
    explicit BackStepAttack(const InitArg& arg);
    ~BackStepAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x110
    const int* mWeaponIdx_s{};
    // static_param at offset 0x118
    const float* mMoveDist_s{};
    // static_param at offset 0x120
    const float* mJustAvoidSideDist_s{};
    // static_param at offset 0x128
    const float* mJustAvoidBackDist_s{};
    // static_param at offset 0x130
    const float* mJustAvoidAngle_s{};
};

}  // namespace uking::action
