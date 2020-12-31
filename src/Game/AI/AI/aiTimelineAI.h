#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TimelineAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TimelineAI, ksys::act::ai::Ai)
public:
    explicit TimelineAI(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mIntervalToCheckSchedule_s{};
};

}  // namespace uking::ai
