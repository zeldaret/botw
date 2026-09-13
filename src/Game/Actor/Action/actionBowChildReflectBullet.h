#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildReflectBullet : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildReflectBullet, ksys::act::ai::Action)
public:
    explicit BowChildReflectBullet(const InitArg& arg);
    ~BowChildReflectBullet() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMoveSpeed_s{};
    // static_param at offset 0x28
    const float* mOffsetLength_s{};
    // static_param at offset 0x30
    const float* mTargetOffsetY_s{};
    // static_param at offset 0x38
    const float* mTargetMoveOffset_s{};
    // static_param at offset 0x40
    const float* mTargetMoveOffsetRandRange_s{};
    // static_param at offset 0x48
    const float* mMoveRotateRate_s{};
    // static_param at offset 0x50
    const float* mMoveRotateMax_s{};
    // static_param at offset 0x58
    const float* mMoveRotateMin_s{};
    // dynamic_param at offset 0x60
    int* mID_d{};
    // dynamic_param at offset 0x68
    float* mXRotateAngle_d{};
    // dynamic_param at offset 0x70
    bool* mIsReflectAmongChild_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mMoveTargetPos_d{};
    // dynamic_param at offset 0x88
    ksys::act::BaseProcLink* mParentActor_d{};
};

}  // namespace uking::action
