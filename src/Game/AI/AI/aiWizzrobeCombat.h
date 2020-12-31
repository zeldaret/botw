#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeCombat : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeCombat, ksys::act::ai::Ai)
public:
    explicit WizzrobeCombat(const InitArg& arg);
    ~WizzrobeCombat() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeatherMagicRate_s{};
    // static_param at offset 0x40
    const int* mSummonRate_s{};
    // static_param at offset 0x48
    const int* mSummonBufferSize_s{};
    // static_param at offset 0x50
    const int* mMaxHeightLevel_s{};
    // static_param at offset 0x58
    const int* mSummonCount_s{};
    // static_param at offset 0x60
    const float* mAttackLength_s{};
    // static_param at offset 0x68
    const float* mHeightOffset_s{};
    // static_param at offset 0x70
    sead::SafeString mSummonBufferKey_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mTargetOffset_s{};
    // aitree_variable at offset 0x88
    int* mSummonCount_a{};
    // aitree_variable at offset 0x90
    bool* mIsWizzrobeInBattleAreaFlag_a{};
};

}  // namespace uking::ai
