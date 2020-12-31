#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LinkTagCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LinkTagCheck, ksys::act::ai::Ai)
public:
    explicit LinkTagCheck(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mSignalType_s{};
    // static_param at offset 0x40
    const int* mSetEnableJobTimerTiming_s{};
    // static_param at offset 0x48
    const bool* mIsNotConnectOn_s{};
    // static_param at offset 0x50
    const bool* mIsCheckChildEnd_s{};
};

}  // namespace uking::ai
