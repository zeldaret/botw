#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabRightWalk : public MoveBase {
    SEAD_RTTI_OVERRIDE(GrabRightWalk, MoveBase)
public:
    explicit GrabRightWalk(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
