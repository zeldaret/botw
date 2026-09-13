#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchTimer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwitchTimer, ksys::act::ai::Ai)
public:
    explicit SwitchTimer(const InitArg& arg);
    ~SwitchTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mWaitTime_m{};
};

}  // namespace uking::ai
