#pragma once

#include "Game/AI/AI/aiShootingEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockBattle : public ShootingEnemyBattle {
    SEAD_RTTI_OVERRIDE(OctarockBattle, ShootingEnemyBattle)
public:
    explicit OctarockBattle(const InitArg& arg);
    ~OctarockBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc8
    const float* mActorDisplayRadius_s{};
    // static_param at offset 0xd0
    const float* mAttackDistMin_s{};
    // static_param at offset 0xd8
    const bool* mIsAttackOnlyOutScreen_s{};
    // static_param at offset 0xe0
    const bool* mIsHideMode_s{};
    // static_param at offset 0xe8
    const bool* mIsFirstAttackIntervalZero_s{};
    // static_param at offset 0xf0
    const bool* mIsLostAttack_s{};
    // static_param at offset 0xf8
    sead::SafeString mShootActorKey_s{};
    // static_param at offset 0x108
    sead::SafeString mVacuumPartsKey_s{};
};

}  // namespace uking::ai
