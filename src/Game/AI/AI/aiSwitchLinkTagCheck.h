#pragma once

#include "Game/AI/AI/aiSwitchAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchLinkTagCheck : public SwitchAI {
    SEAD_RTTI_OVERRIDE(SwitchLinkTagCheck, SwitchAI)
public:
    explicit SwitchLinkTagCheck(const InitArg& arg);
    ~SwitchLinkTagCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mSignalType_s{};
    // static_param at offset 0x40
    const int* mSetEnableJobTimerTiming_s{};
};

}  // namespace uking::ai
