#pragma once

#include "Game/AI/Action/actionForkTimer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkTimerForceResetCondition : public ForkTimer {
    SEAD_RTTI_OVERRIDE(ForkTimerForceResetCondition, ForkTimer)
public:
    explicit ForkTimerForceResetCondition(const InitArg& arg);
    ~ForkTimerForceResetCondition() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const int* mResetCondition_s{};
};

}  // namespace uking::action
