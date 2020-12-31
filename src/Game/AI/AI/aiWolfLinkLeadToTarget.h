#pragma once

#include "Game/AI/AI/aiLeadToTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkLeadToTarget : public LeadToTarget {
    SEAD_RTTI_OVERRIDE(WolfLinkLeadToTarget, LeadToTarget)
public:
    explicit WolfLinkLeadToTarget(const InitArg& arg);
    ~WolfLinkLeadToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
