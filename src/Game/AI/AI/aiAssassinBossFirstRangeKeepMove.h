#pragma once

#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossFirstRangeKeepMove : public EnemyRangeKeepMove {
    SEAD_RTTI_OVERRIDE(AssassinBossFirstRangeKeepMove, EnemyRangeKeepMove)
public:
    explicit AssassinBossFirstRangeKeepMove(const InitArg& arg);
    ~AssassinBossFirstRangeKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x110
    const float* mNoMoveAnchorDist_s{};
    // static_param at offset 0x118
    sead::SafeString mAnchorName_s{};
};

}  // namespace uking::ai
