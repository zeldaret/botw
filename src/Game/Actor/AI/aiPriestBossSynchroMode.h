#pragma once

#include "Game/Actor/AI/aiPriestBoss.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossSynchroMode : public PriestBoss {
    SEAD_RTTI_OVERRIDE(PriestBossSynchroMode, PriestBoss)
public:
    explicit PriestBossSynchroMode(const InitArg& arg);
    ~PriestBossSynchroMode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x40
    int* mEquipWeaponBufIndex_a{};
    // aitree_variable at offset 0x48
    bool* mReturnFromBananaMode_a{};
};

}  // namespace uking::ai
