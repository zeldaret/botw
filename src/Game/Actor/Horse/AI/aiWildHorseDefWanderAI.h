#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WildHorseDefWanderAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WildHorseDefWanderAI, ksys::act::ai::Ai)
public:
    explicit WildHorseDefWanderAI(const InitArg& arg);
    ~WildHorseDefWanderAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mChangeWaitRate_s{};
    // static_param at offset 0x40
    const float* mMaxWaitTime_s{};
    // static_param at offset 0x48
    const float* mMinWaitTime_s{};
};

}  // namespace uking::ai
