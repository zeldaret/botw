#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNormal, ksys::act::ai::Ai)
public:
    explicit EnemyNormal(const InitArg& arg);
    ~EnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    int* mPlayerSoundSealRefCount_a{};
    // aitree_variable at offset 0x40
    int* mSealNoPlayerAwnRequestCount_a{};
    // static_param at offset 0x70
    const int* mWeaponIdx_s{};
    // static_param at offset 0x78
    const int* mSoundLostTimer_s{};
    // static_param at offset 0x80
    const int* mNoActionReactTimeMin_s{};
    // static_param at offset 0x88
    const int* mNoActionReactTimeMax_s{};
    // static_param at offset 0x90
    const float* mTerritoryArea_s{};
    // static_param at offset 0x98
    const float* mNpcTerritoryArea_s{};
    // static_param at offset 0xa0
    const float* mNoPlayerTerritoryArea_s{};
    // static_param at offset 0xa8
    const float* mSpreadDist_s{};
    // static_param at offset 0xb0
    const float* mEnlargeAwnRatio_s{};
    // static_param at offset 0xb8
    const float* mNoticeTerrorLevel_s{};
    // static_param at offset 0xc0
    const float* mSpeadDist2_s{};
    // static_param at offset 0xc8
    const float* mHomePosRadius_s{};
    // static_param at offset 0xd0
    const float* mSubsTerritoryArea_s{};
    // static_param at offset 0xd8
    const float* mLostExtinguishFireDist_s{};
    // static_param at offset 0xe0
    const float* mShortRangeTerritoryArea_s{};
    // static_param at offset 0xe8
    const float* mCloseRangeTerritoryArea_s{};
    // static_param at offset 0xf0
    const float* mPressBreakObject_s{};
    // static_param at offset 0xf8
    const float* mTerritoryHeight_s{};
    // static_param at offset 0x100
    const bool* mIsMindDoubtTarget_s{};
    // static_param at offset 0x108
    sead::SafeString mFortressTag_s{};
    // map_unit_param at offset 0x118
    const float* mTerritoryArea_m{};
};

}  // namespace uking::ai
