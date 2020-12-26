#pragma once

#include "Game/AI/Action/actionForkDynActorNoTargetSelfBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDynActorNoTargetSelf : public ForkDynActorNoTargetSelfBase {
    SEAD_RTTI_OVERRIDE(ForkDynActorNoTargetSelf, ForkDynActorNoTargetSelfBase)
public:
    explicit ForkDynActorNoTargetSelf(const InitArg& arg);
    ~ForkDynActorNoTargetSelf() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x30
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
