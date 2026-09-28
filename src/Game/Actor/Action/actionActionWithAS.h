#pragma once

#include "Game/Actor/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActionWithAS : public StopBase {
    SEAD_RTTI_OVERRIDE(ActionWithAS, StopBase)
public:
    explicit ActionWithAS(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
