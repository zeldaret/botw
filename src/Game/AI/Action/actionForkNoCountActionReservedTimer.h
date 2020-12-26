#pragma once

#include "Game/AI/Action/actionForkTimer.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNoCountActionReservedTimer : public ForkTimer {
    SEAD_RTTI_OVERRIDE(ForkNoCountActionReservedTimer, ForkTimer)
public:
    explicit ForkNoCountActionReservedTimer(const InitArg& arg);
    ~ForkNoCountActionReservedTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x48
    bool* mIsNextActionReserved_a{};
};

}  // namespace uking::action
