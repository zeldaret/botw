#pragma once

#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageBackwardBase : public TakeHitImpactForce {
    SEAD_RTTI_OVERRIDE(SmallDamageBackwardBase, TakeHitImpactForce)
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
