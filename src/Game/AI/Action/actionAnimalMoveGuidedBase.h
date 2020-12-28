#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalMoveGuidedBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnimalMoveGuidedBase, ksys::act::ai::Action)
public:
    explicit AnimalMoveGuidedBase(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mMinUseGear_s{};
    // static_param at offset 0x28
    const int* mMaxUseGear_s{};
    // static_param at offset 0x30
    const int* mUseGearType_s{};
    // static_param at offset 0x38
    const int* mAutoStopAndTurnMode_s{};
    // static_param at offset 0x40
    const int* mMinGearAtAutoGearDown_s{};
    // static_param at offset 0x48
    const float* mGoalDistanceTolerance_s{};
    // static_param at offset 0x50
    const bool* mCanUseHorseGearInput_s{};
    // static_param at offset 0x58
    const bool* mIsAutoGearDownEnabled_s{};
    // static_param at offset 0x60
    const bool* mHasToDecelerateNearGoal_s{};
    // static_param at offset 0x68
    const bool* mWaitUntilPathSucceeded_s{};
};

}  // namespace uking::action
