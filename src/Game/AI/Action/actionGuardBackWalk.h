#pragma once

#include "Game/AI/Action/actionBackWalkEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardBackWalk : public BackWalkEx {
    SEAD_RTTI_OVERRIDE(GuardBackWalk, BackWalkEx)
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
