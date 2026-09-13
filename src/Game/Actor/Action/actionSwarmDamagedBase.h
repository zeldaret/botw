#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwarmDamagedBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwarmDamagedBase, ksys::act::ai::Action)
public:
    explicit SwarmDamagedBase(const InitArg& arg);
    ~SwarmDamagedBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mIgnoreHitGroundTime_s{};
    // static_param at offset 0x28
    const int* mTime_s{};
    // static_param at offset 0x30
    const float* mRiseSpeedMin_s{};
    // static_param at offset 0x38
    const float* mSubAccRateMin_s{};
    // static_param at offset 0x40
    const float* mSubAccRateMax_s{};
    // static_param at offset 0x48
    const float* mSpeed_s{};
    // static_param at offset 0x50
    const bool* mIsCreateDeadActor_s{};
    // map_unit_param at offset 0x58
    const int* mSubUnitNum_m{};
    // map_unit_param at offset 0x60
    const int* mPatternID_m{};
};

}  // namespace uking::action
