#pragma once

#include "Game/AI/AI/aiSwitchAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchWindHit : public SwitchAI {
    SEAD_RTTI_OVERRIDE(SwitchWindHit, SwitchAI)
public:
    explicit SwitchWindHit(const InitArg& arg);
    ~SwitchWindHit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mWaitTime_s{};
};

}  // namespace uking::ai
