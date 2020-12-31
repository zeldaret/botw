#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(GanonReaction, EnemyDefaultReaction)
public:
    explicit GanonReaction(const InitArg& arg);
    ~GanonReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
