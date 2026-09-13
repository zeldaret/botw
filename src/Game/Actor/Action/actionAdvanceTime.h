#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AdvanceTime : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AdvanceTime, ksys::act::ai::Action)
public:
    explicit AdvanceTime(const InitArg& arg);
    ~AdvanceTime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mDestTime_d{};
    // dynamic_param at offset 0x28
    int* mDirectTime_d{};
    // dynamic_param at offset 0x30
    int* mPassTime_d{};
    // dynamic_param at offset 0x38
    bool* mActReset_d{};
};

}  // namespace uking::action
