#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FadeInOutWithOptions : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FadeInOutWithOptions, ksys::act::ai::Action)
public:
    explicit FadeInOutWithOptions(const InitArg& arg);
    ~FadeInOutWithOptions() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mFadeType_s{};
    // static_param at offset 0x28
    const float* mFadeStartFrame_s{};
    // static_param at offset 0x30
    const float* mFadeFinishFrame_s{};
    // static_param at offset 0x38
    const bool* mToggleAttention_s{};
    // static_param at offset 0x40
    const bool* mToggleAwareness_s{};
    // static_param at offset 0x48
    const bool* mToggleEffects_s{};
    // static_param at offset 0x50
    const bool* mToggleCollision_s{};
    // static_param at offset 0x58
    const bool* mToggleHorseOptions_s{};
};

}  // namespace uking::action
