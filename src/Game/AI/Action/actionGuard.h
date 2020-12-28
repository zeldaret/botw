#pragma once

#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Guard : public TakeHitImpactForce {
    SEAD_RTTI_OVERRIDE(Guard, TakeHitImpactForce)
public:
    explicit Guard(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const float* mRotSubsAngRate_s{};
};

}  // namespace uking::action
