#pragma once

#include "Game/Actor/Action/actionNormalBackWalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackWalk : public NormalBackWalk {
    SEAD_RTTI_OVERRIDE(BackWalk, NormalBackWalk)
public:
    explicit BackWalk(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
