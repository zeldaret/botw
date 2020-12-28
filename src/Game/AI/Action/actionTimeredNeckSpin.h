#pragma once

#include "Game/AI/Action/actionNeckSpin.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TimeredNeckSpin : public NeckSpin {
    SEAD_RTTI_OVERRIDE(TimeredNeckSpin, NeckSpin)
public:
    explicit TimeredNeckSpin(const InitArg& arg);
    ~TimeredNeckSpin() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x68
    const int* mTime_s{};
    // static_param at offset 0x70
    const float* mSpinSpeedRatio_s{};
    // static_param at offset 0x78
    const float* mInitSpinSpeed_s{};
};

}  // namespace uking::action
