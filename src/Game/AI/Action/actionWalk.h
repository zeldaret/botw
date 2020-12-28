#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Walk : public MoveBase {
    SEAD_RTTI_OVERRIDE(Walk, MoveBase)
public:
    explicit Walk(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
