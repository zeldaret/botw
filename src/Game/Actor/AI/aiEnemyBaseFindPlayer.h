#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyBaseFindPlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyBaseFindPlayer, ksys::act::ai::Ai)
public:
    explicit EnemyBaseFindPlayer(const InitArg& arg);
    ~EnemyBaseFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mSurpriseAttackPer_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const int* mLostTimer_s{};
    // static_param at offset 0x50
    const int* mSurpriseAttackTime_s{};
    // static_param at offset 0x58
    const int* mSurpriseAttackTimeRand_s{};
    // static_param at offset 0x60
    const int* mRerouteTimeMin_s{};
    // static_param at offset 0x68
    const int* mRerouteTimeMax_s{};
    // static_param at offset 0x70
    const int* mRestreintTime_s{};
    // static_param at offset 0x78
    const int* mRetTiredFromTime_s{};
    // static_param at offset 0x80
    const float* mSurpriseAttackRange_s{};
    // static_param at offset 0x88
    const float* mAttackRange_s{};
    // static_param at offset 0x90
    const float* mAttackVMin_s{};
    // static_param at offset 0x98
    const float* mAttackVMax_s{};
    // static_param at offset 0xa0
    const float* mSwiftAttackVMin_s{};
    // static_param at offset 0xa8
    const float* mSwiftAttackVMax_s{};
    // static_param at offset 0xb0
    const float* mRestreintTiredDist_s{};
    // static_param at offset 0xb8
    const float* mForceFirstAttackDist_s{};
    // static_param at offset 0xc0
    const float* mRetForceFirstAttackDist_s{};
    // static_param at offset 0xc8
    const float* mPathTooLongDist_s{};
    // static_param at offset 0xd0
    const float* mNoSearchFromTiredDist_s{};
    // aitree_variable at offset 0xd8
    bool* mIsTryingReturnRestreint_a{};
};

}  // namespace uking::ai
