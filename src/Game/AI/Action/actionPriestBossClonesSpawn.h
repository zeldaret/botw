#pragma once

#include "Game/AI/Action/actionPriestBossClonesSpawnForDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossClonesSpawn : public PriestBossClonesSpawnForDemo {
    SEAD_RTTI_OVERRIDE(PriestBossClonesSpawn, PriestBossClonesSpawnForDemo)
public:
    explicit PriestBossClonesSpawn(const InitArg& arg);
    ~PriestBossClonesSpawn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    sead::SafeString mASNameForAITree_s{};
    // dynamic_param at offset 0x98
    int* mDelayFrame_d{};
};

}  // namespace uking::action
