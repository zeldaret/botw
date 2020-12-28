#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardLoop : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(GuardLoop, ActionWithPosAngReduce)
public:
    explicit GuardLoop(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
