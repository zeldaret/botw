#pragma once

#include "Game/AI/AI/aiSwarmEscapeDie.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwarmStopTimerEscape : public SwarmEscapeDie {
    SEAD_RTTI_OVERRIDE(SwarmStopTimerEscape, SwarmEscapeDie)
public:
    explicit SwarmStopTimerEscape(const InitArg& arg);
    ~SwarmStopTimerEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x70
    sead::SafeString mStopActorName_s{};
};

}  // namespace uking::ai
