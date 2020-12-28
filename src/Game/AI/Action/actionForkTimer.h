#pragma once

#include "Game/AI/Action/actionForkTimerBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkTimer : public ForkTimerBase {
    SEAD_RTTI_OVERRIDE(ForkTimer, ForkTimerBase)
public:
    explicit ForkTimer(const InitArg& arg);
    ~ForkTimer() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWaitFrame_s{};
    // static_param at offset 0x40
    const int* mWaitFrameRand_s{};
};

}  // namespace uking::action
