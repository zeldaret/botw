#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabLeftWalk : public MoveBase {
    SEAD_RTTI_OVERRIDE(GrabLeftWalk, MoveBase)
public:
    explicit GrabLeftWalk(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
