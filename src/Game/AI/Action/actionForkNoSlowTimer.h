#pragma once

#include "Game/AI/Action/actionForkTimer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNoSlowTimer : public ForkTimer {
    SEAD_RTTI_OVERRIDE(ForkNoSlowTimer, ForkTimer)
public:
    explicit ForkNoSlowTimer(const InitArg& arg);
    ~ForkNoSlowTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
