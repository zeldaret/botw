#pragma once

#include "Game/AI/AI/aiSiteBossSwordApproachRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossFastWarpAttack : public SiteBossSwordApproachRoot {
    SEAD_RTTI_OVERRIDE(PriestBossFastWarpAttack, SiteBossSwordApproachRoot)
public:
    explicit PriestBossFastWarpAttack(const InitArg& arg);
    ~PriestBossFastWarpAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
