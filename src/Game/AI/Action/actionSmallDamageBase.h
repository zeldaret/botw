#pragma once

#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageBase : public TakeHitImpactForce {
    SEAD_RTTI_OVERRIDE(SmallDamageBase, TakeHitImpactForce)
public:
    explicit SmallDamageBase(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
