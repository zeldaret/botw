#pragma once

#include "Game/AI/AI/aiShootingEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneOctarockBattle : public ShootingEnemyBattle {
    SEAD_RTTI_OVERRIDE(StoneOctarockBattle, ShootingEnemyBattle)
public:
    explicit StoneOctarockBattle(const InitArg& arg);
    ~StoneOctarockBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
