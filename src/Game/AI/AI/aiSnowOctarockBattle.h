#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SnowOctarockBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(SnowOctarockBattle, EnemyBattle)
public:
    explicit SnowOctarockBattle(const InitArg& arg);
    ~SnowOctarockBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    sead::SafeString mVacuumPartsKey_s{};
    // static_param at offset 0xa0
    sead::SafeString mShootActorKey_s{};
};

}  // namespace uking::ai
