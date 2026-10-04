#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCSuspend : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCSuspend, ksys::act::ai::Ai)
public:
    explicit NPCSuspend(const InitArg& arg);
    ~NPCSuspend() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWaitTime_s{};
    // static_param at offset 0x40
    const int* mEndMoveTime_s{};
    // static_param at offset 0x48
    const int* mRetryCount_s{};
    // static_param at offset 0x50
    const float* mSearchRadius_s{};
    // dynamic_param at offset 0x58
    sead::SafeString* mASName_d{};
};

}  // namespace uking::ai
