#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDrownTimer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkDrownTimer, ksys::act::ai::Action)
public:
    explicit ForkDrownTimer(const InitArg& arg);
    ~ForkDrownTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const float* mInWaterDepth_s{};
};

}  // namespace uking::action
