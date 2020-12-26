#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildDeviceGaleArrow : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildDeviceGaleArrow, ksys::act::ai::Action)
public:
    explicit BowChildDeviceGaleArrow(const InitArg& arg);
    ~BowChildDeviceGaleArrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxMoveSpeed_s{};
    // static_param at offset 0x28
    const float* mRotateSpeedMax_s{};
    // static_param at offset 0x30
    const float* mRotateAccel_s{};
    // static_param at offset 0x38
    const float* mRotateOffset_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mCenterOffset_s{};
    // dynamic_param at offset 0x48
    int* mID_d{};
    // dynamic_param at offset 0x50
    float* mXRotateAngle_d{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mParentActor_d{};
};

}  // namespace uking::action
