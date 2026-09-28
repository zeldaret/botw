#pragma once

#include "Game/Actor/Action/actionKnockBackHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Guard : public KnockBackHitImpactForce {
    SEAD_RTTI_OVERRIDE(Guard, KnockBackHitImpactForce)
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
