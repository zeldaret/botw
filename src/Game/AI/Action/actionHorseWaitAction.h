#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseWaitAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseWaitAction, ksys::act::ai::Action)
public:
    explicit HorseWaitAction(const InitArg& arg);
    ~HorseWaitAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mUseGearType_s{};
    // static_param at offset 0x28
    const float* mSmoothStopFrames_s{};
    // static_param at offset 0x30
    const float* mSmoothStopFramesGear3_s{};
    // static_param at offset 0x38
    const float* mMinFramesGear1_s{};
    // static_param at offset 0x40
    const bool* mIsCourbetteEnabled_s{};
    // static_param at offset 0x48
    const bool* mIsLight_s{};
};

}  // namespace uking::action
