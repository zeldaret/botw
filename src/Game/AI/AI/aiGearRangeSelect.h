#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GearRangeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GearRangeSelect, ksys::act::ai::Ai)
public:
    explicit GearRangeSelect(const InitArg& arg);
    ~GearRangeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mGearThreashold_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
};

}  // namespace uking::ai
