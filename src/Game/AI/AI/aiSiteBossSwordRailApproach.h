#pragma once

#include "Game/AI/AI/aiSiteBossSwordApproachRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordRailApproach : public SiteBossSwordApproachRoot {
    SEAD_RTTI_OVERRIDE(SiteBossSwordRailApproach, SiteBossSwordApproachRoot)
public:
    explicit SiteBossSwordRailApproach(const InitArg& arg);
    ~SiteBossSwordRailApproach() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0xc0
    bool* mIsResetOldMoveIdx_d{};
};

}  // namespace uking::ai
