#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(SandwormReaction, EnemyDefaultReaction)
public:
    explicit SandwormReaction(const InitArg& arg);
    ~SandwormReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
