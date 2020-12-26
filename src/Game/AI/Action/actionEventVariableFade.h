#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventVariableFade : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventVariableFade, ksys::act::ai::Action)
public:
    explicit EventVariableFade(const InitArg& arg);
    ~EventVariableFade() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mClipIndex_d{};
    // dynamic_param at offset 0x28
    int* mColor_d{};
    // dynamic_param at offset 0x30
    float* mDuration_d{};
    // dynamic_param at offset 0x38
    float* mFadeTime_d{};
};

}  // namespace uking::action
