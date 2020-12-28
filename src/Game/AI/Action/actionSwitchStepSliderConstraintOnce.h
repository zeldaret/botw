#pragma once

#include "Game/AI/Action/actionSwitchStepSliderConstraint.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwitchStepSliderConstraintOnce : public SwitchStepSliderConstraint {
    SEAD_RTTI_OVERRIDE(SwitchStepSliderConstraintOnce, SwitchStepSliderConstraint)
public:
    explicit SwitchStepSliderConstraintOnce(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
