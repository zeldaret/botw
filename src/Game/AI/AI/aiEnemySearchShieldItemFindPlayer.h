#pragma once

#include "Game/AI/AI/aiLandHumEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemySearchShieldItemFindPlayer : public LandHumEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(EnemySearchShieldItemFindPlayer, LandHumEnemyFindPlayer)
public:
    explicit EnemySearchShieldItemFindPlayer(const InitArg& arg);
    ~EnemySearchShieldItemFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1e8
    const int* mShieldIdx_s{};
    // static_param at offset 0x1f0
    const float* mSearchShieldDist_s{};
    // static_param at offset 0x1f8
    const float* mNoShieldSearchDist_s{};
    // static_param at offset 0x200
    const float* mSearchObjectDist_s{};
    // static_param at offset 0x208
    const float* mItemChaseableSpd_s{};
    // static_param at offset 0x210
    const float* mItemChasealeRot_s{};
    // static_param at offset 0x218
    const bool* mCanGrabHeavy_s{};
};

}  // namespace uking::ai
