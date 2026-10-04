#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockServiceHideWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OctarockServiceHideWait, ksys::act::ai::Ai)
public:
    explicit OctarockServiceHideWait(const InitArg& arg);
    ~OctarockServiceHideWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSafeAreaDist_s{};
    // static_param at offset 0x40
    const float* mSafeAreaDistRange_s{};
    // static_param at offset 0x48
    const float* mMinWaitTime_s{};
    // static_param at offset 0x50
    const float* mMinWaitTimeRand_s{};
    // static_param at offset 0x58
    const float* mNoticeTerrorLevel_s{};
    // static_param at offset 0x60
    const float* mNoticeWorryRange_s{};
};

}  // namespace uking::ai
