#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CustomDuckingStartAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CustomDuckingStartAction, ksys::act::ai::Action)
public:
    explicit CustomDuckingStartAction(const InitArg& arg);
    ~CustomDuckingStartAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    float* mVolume_d{};
    // dynamic_param at offset 0x28
    float* mFadeOutSec_d{};
    // dynamic_param at offset 0x30
    float* mFadeInSec_d{};
    // dynamic_param at offset 0x38
    float* mStartDelaySec_d{};
    // dynamic_param at offset 0x40
    sead::SafeString mTargetGroups_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mExceptGroups_d{};
};

}  // namespace uking::action
