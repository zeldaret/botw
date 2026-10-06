#pragma once

#include "Game/Actor/AI/aiGiantEnemyFindPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemFindPlayer : public GiantEnemyFindPlayer {
    SEAD_RTTI_OVERRIDE(GolemFindPlayer, GiantEnemyFindPlayer)
public:
    explicit GolemFindPlayer(const InitArg& arg);
    ~GolemFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x140
    const float* mSearchExplosiveDist_s{};
};

}  // namespace uking::ai
