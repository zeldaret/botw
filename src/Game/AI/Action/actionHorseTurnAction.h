#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseTurnAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseTurnAction, ksys::act::ai::Action)
public:
    explicit HorseTurnAction(const InitArg& arg);
    ~HorseTurnAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mGoalDegToleranceAtEnter_s{};
    // static_param at offset 0x28
    const float* mGoalDegTolerance_s{};
    // dynamic_param at offset 0x30
    sead::Vector3f* mTargetDirection_d{};
};

}  // namespace uking::action
