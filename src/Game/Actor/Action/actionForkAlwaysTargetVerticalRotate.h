#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysTargetVerticalRotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAlwaysTargetVerticalRotate, ksys::act::ai::Action)
public:
    explicit ForkAlwaysTargetVerticalRotate(const InitArg& arg);
    ~ForkAlwaysTargetVerticalRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpdMax_s{};
    // static_param at offset 0x28
    const float* mRotSpdRatio_s{};
    // static_param at offset 0x30
    const bool* mIsUpdateTargetPos_s{};
    // static_param at offset 0x38
    const bool* mIsIgnoreY_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mOtherAxis_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
