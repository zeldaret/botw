#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventChangeShadowNearAndFar : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventChangeShadowNearAndFar, ksys::act::ai::Action)
public:
    explicit EventChangeShadowNearAndFar(const InitArg& arg);
    ~EventChangeShadowNearAndFar() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mManualNearValue_d{};
    // dynamic_param at offset 0x28
    float* mManualFarValue_d{};
    // dynamic_param at offset 0x30
    bool* mIsNearSetManual_d{};
    // dynamic_param at offset 0x38
    bool* mIsFarSetManual_d{};
};

}  // namespace uking::action
