#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgShootArrow : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgShootArrow, ksys::act::ai::Action)
public:
    explicit ForkASTrgShootArrow(const InitArg& arg);
    ~ForkASTrgShootArrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mIsEndState_s{};
    // static_param at offset 0x30
    const int* mSeqBank_s{};
    // static_param at offset 0x38
    const int* mTargetBone_s{};
    // static_param at offset 0x40
    const float* mOffsetRangeMin_s{};
    // static_param at offset 0x48
    const float* mOffsetRangeMax_s{};
    // static_param at offset 0x50
    const float* mOffsetRateByDist_s{};
    // static_param at offset 0x58
    const float* mOffsetRangeMinOutOfScreen_s{};
    // static_param at offset 0x60
    const float* mOffsetRangeMaxOutOfScreen_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
