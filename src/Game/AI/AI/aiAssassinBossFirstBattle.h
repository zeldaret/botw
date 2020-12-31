#pragma once

#include "Game/AI/AI/aiEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossFirstBattle : public EnemyBattle {
    SEAD_RTTI_OVERRIDE(AssassinBossFirstBattle, EnemyBattle)
public:
    explicit AssassinBossFirstBattle(const InitArg& arg);
    ~AssassinBossFirstBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mIronBallNum_s{};
    // static_param at offset 0x98
    const float* mGuardAngle_s{};
    // static_param at offset 0xa0
    const float* mAttackInterseptDist_s{};
    // static_param at offset 0xa8
    sead::SafeString mIronBallKeyName_s{};
};

}  // namespace uking::ai
