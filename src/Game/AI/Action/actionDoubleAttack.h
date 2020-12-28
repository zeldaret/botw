#pragma once

#include "Game/AI/Action/actionStepDoubleAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DoubleAttack : public StepDoubleAttack {
    SEAD_RTTI_OVERRIDE(DoubleAttack, StepDoubleAttack)
public:
    explicit DoubleAttack(const InitArg& arg);
    ~DoubleAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
