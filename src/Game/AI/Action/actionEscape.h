#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Escape : public MoveBase {
    SEAD_RTTI_OVERRIDE(Escape, MoveBase)
public:
    explicit Escape(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
