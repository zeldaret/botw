#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSetJustAvoid : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkSetJustAvoid, ksys::act::ai::Action)
public:
    explicit ForkSetJustAvoid(const InitArg& arg);
    ~ForkSetJustAvoid() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mTargetBone_s{};
    // static_param at offset 0x30
    const int* mSeqBank_s{};
    // static_param at offset 0x38
    const float* mJustAvoidAngleL_s{};
    // static_param at offset 0x40
    const float* mJustAvoidAngleR_s{};
    // static_param at offset 0x48
    const float* mJustAvoidDistFar_s{};
    // static_param at offset 0x50
    const float* mJustAvoidDistNear_s{};
    // static_param at offset 0x58
    const bool* mIsAddRangeToFar_s{};
    // static_param at offset 0x60
    const bool* mIsAddRangeToNear_s{};
};

}  // namespace uking::action
