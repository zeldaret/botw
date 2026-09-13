#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmDrivenSpeedBackWalk : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmDrivenSpeedBackWalk, ksys::act::ai::Action)
public:
    explicit AnmDrivenSpeedBackWalk(const InitArg& arg);
    ~AnmDrivenSpeedBackWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const int* mWeaponIdx_s{};
    // static_param at offset 0x30
    const float* mRotSpd_s{};
    // static_param at offset 0x38
    const float* mRotAddRatio_s{};
    // static_param at offset 0x40
    const float* mFinishDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
