#pragma once

#include "Game/AI/Action/actionFreeMovingAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkFreeMoving : public FreeMovingAction {
    SEAD_RTTI_OVERRIDE(ForkFreeMoving, FreeMovingAction)
public:
    explicit ForkFreeMoving(const InitArg& arg);
    ~ForkFreeMoving() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
