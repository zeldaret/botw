#pragma once

#include "Game/Actor/Action/actionKnockBackHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageBase : public KnockBackHitImpactForce {
    SEAD_RTTI_OVERRIDE(SmallDamageBase, KnockBackHitImpactForce)
public:
    explicit SmallDamageBase(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
