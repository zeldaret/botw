#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossActorPhaseSecondStart : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossActorPhaseSecondStart, ksys::act::ai::Ai)
public:
    explicit PriestBossActorPhaseSecondStart(const InitArg& arg);
    ~PriestBossActorPhaseSecondStart() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    int* mEquipWeaponBufIndex_a{};
    // aitree_variable at offset 0x40
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
