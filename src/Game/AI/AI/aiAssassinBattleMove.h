#pragma once

#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBattleMove : public EnemyRangeKeepMove {
    SEAD_RTTI_OVERRIDE(AssassinBattleMove, EnemyRangeKeepMove)
public:
    explicit AssassinBattleMove(const InitArg& arg);
    ~AssassinBattleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x110
    const float* mWarpDist_s{};
};

}  // namespace uking::ai
