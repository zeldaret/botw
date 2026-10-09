#pragma once

#include "Game/Actor/Action/actionForkEndByConditionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDynActorNoTargetSelf : public ForkEndByConditionBase {
    SEAD_RTTI_OVERRIDE(ForkDynActorNoTargetSelf, ForkEndByConditionBase)
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
