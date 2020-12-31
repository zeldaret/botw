#pragma once

#include "Game/AI/AI/aiSimpleShootingEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ShootingEnemyFindPlayer : public SimpleShootingEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(ShootingEnemyFindPlayer, SimpleShootingEnemyFindPlayer)
public:
    explicit ShootingEnemyFindPlayer(const InitArg& arg);
    ~ShootingEnemyFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x150
    const int* mReHideTime_s{};
    // static_param at offset 0x158
    const float* mExplosivesAvoidDist_s{};
    // static_param at offset 0x160
    const float* mExplosivesAvoidSpeed_s{};
    // static_param at offset 0x168
    const float* mExplosivesAvoidAng_s{};
    // static_param at offset 0x170
    const float* mHideStartDistMin_s{};
    // static_param at offset 0x178
    const float* mHideStartDistMax_s{};
};

}  // namespace uking::ai
