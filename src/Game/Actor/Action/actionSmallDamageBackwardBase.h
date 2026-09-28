#pragma once

#include "Game/Actor/Action/actionKnockBackHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageBackwardBase : public KnockBackHitImpactForce {
    SEAD_RTTI_OVERRIDE(SmallDamageBackwardBase, KnockBackHitImpactForce)
public:
    explicit SmallDamageBackwardBase(const InitArg& arg);
    ~SmallDamageBackwardBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
