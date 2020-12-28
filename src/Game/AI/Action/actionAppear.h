#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Appear : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(Appear, ActionWithAS)
public:
    explicit Appear(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
