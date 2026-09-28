#pragma once

#include "Game/Actor/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEndByConditionBase : public Fork {
    SEAD_RTTI_OVERRIDE(ForkEndByConditionBase, Fork)
public:
    explicit ForkEndByConditionBase(const InitArg& arg);
    ~ForkEndByConditionBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
