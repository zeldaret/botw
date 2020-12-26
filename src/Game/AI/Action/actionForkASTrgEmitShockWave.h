#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgEmitShockWave : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgEmitShockWave, ksys::act::ai::Action)
public:
    explicit ForkASTrgEmitShockWave(const InitArg& arg);
    ~ForkASTrgEmitShockWave() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mPower_s{};
    // static_param at offset 0x28
    const int* mAttackIntensity_s{};
    // static_param at offset 0x30
    const int* mEmitIntervalTime_s{};
    // static_param at offset 0x38
    const int* mAtMinDamage_s{};
    // static_param at offset 0x40
    const float* mMaxScale_s{};
    // static_param at offset 0x48
    const float* mScaleTime_s{};
    // static_param at offset 0x50
    const bool* mIsGuardPierce_s{};
    // static_param at offset 0x58
    const bool* mIsForceGuardBreak_s{};
    // static_param at offset 0x60
    const bool* mIsIniviciblePierce_s{};
    // static_param at offset 0x68
    const bool* mIsHeavy_s{};
    // static_param at offset 0x70
    sead::SafeString mShockWaveActorName_s{};
    // static_param at offset 0x80
    sead::SafeString mShockWavePartsKey_s{};
};

}  // namespace uking::action
