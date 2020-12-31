#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkFollowWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkFollowWait, ksys::act::ai::Ai)
public:
    explicit WolfLinkFollowWait(const InitArg& arg);
    ~WolfLinkFollowWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTurnThreshold_s{};
    // static_param at offset 0x40
    const float* mLockonTurnThreshold_s{};
};

}  // namespace uking::ai
