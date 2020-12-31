#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeCombatMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeCombatMove, ksys::act::ai::Ai)
public:
    explicit WizzrobeCombatMove(const InitArg& arg);
    ~WizzrobeCombatMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMoveCountMin_s{};
    // static_param at offset 0x40
    const int* mMoveCountMax_s{};
    // static_param at offset 0x48
    const float* mDistY_s{};
    // static_param at offset 0x50
    const float* mRetryLength_s{};
    // static_param at offset 0x58
    const float* mMaxDistXZ_s{};
    // static_param at offset 0x60
    const float* mMinDistXZ_s{};
    // static_param at offset 0x68
    const float* mEscapeLength_s{};
    // static_param at offset 0x70
    sead::SafeString mIgnoreHideActionASName_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mAttPos_d{};
    // aitree_variable at offset 0x90
    bool* mIsWizzrobeInBattleAreaFlag_a{};
};

}  // namespace uking::ai
