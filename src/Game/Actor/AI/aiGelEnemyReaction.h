#pragma once

#include "Game/Actor/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GelEnemyReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(GelEnemyReaction, EnemyDefaultReaction)
public:
    explicit GelEnemyReaction(const InitArg& arg);
    ~GelEnemyReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
