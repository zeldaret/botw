#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WarpActivateTerminal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WarpActivateTerminal, ksys::act::ai::Ai)
public:
    explicit WarpActivateTerminal(const InitArg& arg);
    ~WarpActivateTerminal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDoLimitAngle_s{};
    // static_param at offset 0x40
    const bool* mIsAbleToReboot_s{};
    // static_param at offset 0x48
    const bool* mIsCheckLimit_s{};
    // static_param at offset 0x50
    const bool* mIsRejectMsgForRemains_s{};
    // map_unit_param at offset 0x58
    const int* mRemainsTerminalType_m{};
    // map_unit_param at offset 0x60
    const int* mRemainsTerminalIndex_m{};
};

}  // namespace uking::ai
