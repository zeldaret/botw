#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DefWanderAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DefWanderAI, ksys::act::ai::Ai)
public:
    explicit DefWanderAI(const InitArg& arg);
    ~DefWanderAI() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mFinishChangeCount_s{};
    // static_param at offset 0x40
    const float* mChangeWaitRate_s{};
    // static_param at offset 0x48
    const float* mMaxWaitTime_s{};
    // static_param at offset 0x50
    const float* mMinWaitTime_s{};
    // static_param at offset 0x58
    const bool* mCheckWaitIsChangable_s{};
};

}  // namespace uking::ai
