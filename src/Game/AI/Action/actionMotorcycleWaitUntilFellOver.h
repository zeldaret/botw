#pragma once

#include "Game/AI/Action/actionMotorcycleWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MotorcycleWaitUntilFellOver : public MotorcycleWait {
    SEAD_RTTI_OVERRIDE(MotorcycleWaitUntilFellOver, MotorcycleWait)
public:
    explicit MotorcycleWaitUntilFellOver(const InitArg& arg);
    ~MotorcycleWaitUntilFellOver() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
