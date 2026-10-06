#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SleepNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SleepNormal, ksys::act::ai::Ai)
public:
    explicit SleepNormal(const InitArg& arg);
    ~SleepNormal() override;

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
