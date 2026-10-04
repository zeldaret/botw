#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseLevelFlyMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BattleCloseLevelFlyMoveBase, ksys::act::ai::Action)
public:
    explicit BattleCloseLevelFlyMoveBase(const InitArg& arg);
    ~BattleCloseLevelFlyMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mXZSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mFinRotate_s{};
    // static_param at offset 0x38
    const float* mHorizontalFinRadius_s{};
    // static_param at offset 0x40
    const float* mVerticalFinLength_s{};
    // static_param at offset 0x48
    const float* mTargetHeightOffset_s{};
    // static_param at offset 0x50
    const float* mRotRatio_s{};
    // static_param at offset 0x58
    const float* mRiseSpeed_s{};
    // static_param at offset 0x60
    const float* mDownSpeed_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
