#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AvoidingCloseMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AvoidingCloseMoveBase, ksys::act::ai::Action)
public:
    explicit AvoidingCloseMoveBase(const InitArg& arg);
    ~AvoidingCloseMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mRotSpd_s{};
    // static_param at offset 0x38
    const float* mFinRadius_s{};
    // static_param at offset 0x40
    const float* mFinRotate_s{};
    // static_param at offset 0x48
    const float* mBaseRotRatio_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
