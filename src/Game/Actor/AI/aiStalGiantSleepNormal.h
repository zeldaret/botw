#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalGiantSleepNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalGiantSleepNormal, ksys::act::ai::Ai)
public:
    explicit StalGiantSleepNormal(const InitArg& arg);
    ~StalGiantSleepNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAwakeDelayTime_s{};
    // static_param at offset 0x40
    const bool* mIsAwakenByHearing_s{};
    // static_param at offset 0x48
    const bool* mIsWaitAfterAwaken_s{};
};

}  // namespace uking::ai
