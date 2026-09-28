#pragma once

#include "Game/Actor/Action/actionNormalBackWalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardBackWalk : public NormalBackWalk {
    SEAD_RTTI_OVERRIDE(GuardBackWalk, NormalBackWalk)
public:
    explicit GuardBackWalk(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
