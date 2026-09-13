#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DefEscapeFreeMoveAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DefEscapeFreeMoveAction, ksys::act::ai::Action)
public:
    explicit DefEscapeFreeMoveAction(const InitArg& arg);
    ~DefEscapeFreeMoveAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRunAwaySpeed_s{};
    // static_param at offset 0x28
    const float* mRunAwayAngleSpeed_s{};
    // static_param at offset 0x30
    const float* mRunAwayDistanceMax_s{};
    // static_param at offset 0x38
    const float* mRunAwayDistanceMin_s{};
    // static_param at offset 0x40
    const float* mRunAwayHeightOffset_s{};
    // static_param at offset 0x48
    const float* mAllowRandAngleVertical_s{};
    // static_param at offset 0x50
    const float* mAllowRandAngleHorizontal_s{};
    // static_param at offset 0x58
    const bool* mInWater_s{};
    // static_param at offset 0x60
    const bool* mIsSnake_s{};
    // static_param at offset 0x68
    sead::SafeString mASKeyName_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
