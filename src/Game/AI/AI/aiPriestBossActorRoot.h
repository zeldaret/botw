#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorRoot : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossActorRoot, PriestBossMode)
public:
    explicit PriestBossActorRoot(const InitArg& arg);
    ~PriestBossActorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
