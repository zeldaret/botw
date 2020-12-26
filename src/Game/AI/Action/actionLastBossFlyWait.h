#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossFlyWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossFlyWait, ksys::act::ai::Action)
public:
    explicit LastBossFlyWait(const InitArg& arg);
    ~LastBossFlyWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDamageCounter_s{};
    // static_param at offset 0x28
    const float* mAmplitude_s{};
    // static_param at offset 0x30
    const float* mTime_s{};
    // static_param at offset 0x38
    const float* mMoveRate_s{};
    // static_param at offset 0x40
    const float* mEndTime_s{};
    // static_param at offset 0x48
    const float* mEndTimeRandRange_s{};
    // static_param at offset 0x50
    const float* mBaseYOffset_s{};
    // static_param at offset 0x58
    const bool* mIsChemicalOff_s{};
    // static_param at offset 0x60
    sead::SafeString mWaitAS_s{};
    // dynamic_param at offset 0x70
    bool* mIsResetEndTime_d{};
};

}  // namespace uking::action
