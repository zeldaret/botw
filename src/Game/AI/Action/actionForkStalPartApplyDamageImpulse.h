#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkStalPartApplyDamageImpulse : public Fork {
    SEAD_RTTI_OVERRIDE(ForkStalPartApplyDamageImpulse, Fork)
public:
    explicit ForkStalPartApplyDamageImpulse(const InitArg& arg);
    ~ForkStalPartApplyDamageImpulse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mMaxAddSpeed_s{};
    // static_param at offset 0x38
    const float* mSwordRate_s{};
    // static_param at offset 0x40
    const float* mSpearRate_s{};
    // static_param at offset 0x48
    const float* mLswordRate_s{};
    // static_param at offset 0x50
    const float* mArrowRate_s{};
    // static_param at offset 0x58
    const float* mBombRate_s{};
    // static_param at offset 0x60
    const float* mGustRate_s{};
    // static_param at offset 0x68
    const float* mLargeAttackAddRate_s{};
    // static_param at offset 0x70
    const float* mMaxAddSpeedY_s{};
    // static_param at offset 0x78
    const float* mRotSpd_s{};
    // static_param at offset 0x80
    const float* mFinRotate_s{};
    // static_param at offset 0x88
    const float* mRotAccRatio_s{};
    // static_param at offset 0x90
    const float* mRotAccMaxSpeedRatio_s{};
    // static_param at offset 0x98
    const float* mBaseRotRatio_s{};
    // static_param at offset 0xa0
    const bool* mIsViewHitDir_s{};
};

}  // namespace uking::action
