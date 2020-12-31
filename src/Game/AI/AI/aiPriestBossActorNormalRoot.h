#pragma once

#include "Game/AI/AI/aiPriestBossActorRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorNormalRoot : public PriestBossActorRoot {
    SEAD_RTTI_OVERRIDE(PriestBossActorNormalRoot, PriestBossActorRoot)
public:
    explicit PriestBossActorNormalRoot(const InitArg& arg);
    ~PriestBossActorNormalRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x40
    int* mEquipWeaponBufIndex_a{};
};

}  // namespace uking::ai
