#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonMoveTo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DragonMoveTo, ksys::act::ai::Action)
public:
    explicit DragonMoveTo(const InitArg& arg);
    ~DragonMoveTo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRollMax_s{};
    // static_param at offset 0x28
    const float* mRollSpeed_s{};
    // static_param at offset 0x30
    const float* mRollMaxSpeed_s{};
    // static_param at offset 0x38
    const float* mRollAmount_s{};
    // static_param at offset 0x40
    const float* mRestoreUp_s{};
    // static_param at offset 0x48
    const float* mBackAdjustAngle_s{};
    // static_param at offset 0x50
    const float* mBackAdjustRestoreUp_s{};
    // static_param at offset 0x58
    const float* mFixAngle_s{};
    // static_param at offset 0x60
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mFrontDir_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
