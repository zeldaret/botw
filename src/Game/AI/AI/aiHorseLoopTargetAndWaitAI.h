#pragma once

#include "Game/AI/AI/aiHorseLoopTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseLoopTargetAndWaitAI : public HorseLoopTarget {
    SEAD_RTTI_OVERRIDE(HorseLoopTargetAndWaitAI, HorseLoopTarget)
public:
    explicit HorseLoopTargetAndWaitAI(const InitArg& arg);
    ~HorseLoopTargetAndWaitAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x170
    const float* mChangeWaitRate_s{};
    // static_param at offset 0x178
    const float* mMaxWaitTime_s{};
    // static_param at offset 0x180
    const float* mMinWaitTime_s{};
};

}  // namespace uking::ai
