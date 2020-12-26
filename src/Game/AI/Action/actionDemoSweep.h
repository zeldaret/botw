#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoSweep : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoSweep, ksys::act::ai::Action)
public:
    explicit DemoSweep(const InitArg& arg);
    ~DemoSweep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mDynScalingTime_d{};
};

}  // namespace uking::action
