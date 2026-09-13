#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TimeControlTagRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TimeControlTagRoot, ksys::act::ai::Ai)
public:
    explicit TimeControlTagRoot(const InitArg& arg);
    ~TimeControlTagRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mStartTime_m{};
    // map_unit_param at offset 0x40
    const int* mEndTime_m{};
    // map_unit_param at offset 0x48
    const int* mStartTimeMinute_m{};
    // map_unit_param at offset 0x50
    const int* mEndTimeMinute_m{};
    // map_unit_param at offset 0x58
    const bool* mIsDirectTime_m{};
    // map_unit_param at offset 0x60
    const bool* mIsMorningA_m{};
    // map_unit_param at offset 0x68
    const bool* mIsMorningB_m{};
    // map_unit_param at offset 0x70
    const bool* mIsNoonA_m{};
    // map_unit_param at offset 0x78
    const bool* mIsNoonB_m{};
    // map_unit_param at offset 0x80
    const bool* mIsEveningA_m{};
    // map_unit_param at offset 0x88
    const bool* mIsEveningB_m{};
    // map_unit_param at offset 0x90
    const bool* mIsNightA_m{};
    // map_unit_param at offset 0x98
    const bool* mIsNightB_m{};
};

}  // namespace uking::ai
