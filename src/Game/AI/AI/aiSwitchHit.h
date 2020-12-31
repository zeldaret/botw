#pragma once

#include "Game/AI/AI/aiSwitchAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchHit : public SwitchAI {
    SEAD_RTTI_OVERRIDE(SwitchHit, SwitchAI)
public:
    explicit SwitchHit(const InitArg& arg);
    ~SwitchHit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mWaitTime_s{};
};

}  // namespace uking::ai
