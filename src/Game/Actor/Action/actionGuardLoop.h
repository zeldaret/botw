#pragma once

#include "Game/Actor/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardLoop : public StopBase {
    SEAD_RTTI_OVERRIDE(GuardLoop, StopBase)
public:
    explicit GuardLoop(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
