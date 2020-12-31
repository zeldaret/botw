#pragma once

#include "Game/AI/AI/aiSwitchAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchRightAndWrong : public SwitchAI {
    SEAD_RTTI_OVERRIDE(SwitchRightAndWrong, SwitchAI)
public:
    explicit SwitchRightAndWrong(const InitArg& arg);
    ~SwitchRightAndWrong() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mWaitTime_s{};
};

}  // namespace uking::ai
