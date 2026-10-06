#pragma once

#include "Game/Actor/AI/aiPriestBoss.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossCloneBulletRoot : public PriestBoss {
    SEAD_RTTI_OVERRIDE(PriestBossCloneBulletRoot, PriestBoss)
public:
    explicit PriestBossCloneBulletRoot(const InitArg& arg);
    ~PriestBossCloneBulletRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x40
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
