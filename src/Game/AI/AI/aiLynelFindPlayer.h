#pragma once

#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelFindPlayer : public EnemyBaseFindPlayer {
    SEAD_RTTI_OVERRIDE(LynelFindPlayer, EnemyBaseFindPlayer)
public:
    explicit LynelFindPlayer(const InitArg& arg);
    ~LynelFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x140
    int* mLynelAIFlags_a{};
};

}  // namespace uking::ai
