#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PreSleepCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreSleepCheck, ksys::act::ai::Ai)
public:
    explicit PreSleepCheck(const InitArg& arg);
    ~PreSleepCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCheckDist_s{};
    // static_param at offset 0x40
    const float* mCheckRadius_s{};
};

}  // namespace uking::ai
