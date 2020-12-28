#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Rebound : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(Rebound, ActionWithAS)
public:
    explicit Rebound(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
