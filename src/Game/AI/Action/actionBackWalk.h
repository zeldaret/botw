#pragma once

#include "Game/AI/Action/actionBackWalkEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackWalk : public BackWalkEx {
    SEAD_RTTI_OVERRIDE(BackWalk, BackWalkEx)
public:
    explicit BackWalk(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
