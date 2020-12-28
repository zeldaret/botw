#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GrabAndShoot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GrabAndShoot, ksys::act::ai::Action)
public:
    explicit GrabAndShoot(const InitArg& arg);
    ~GrabAndShoot() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mGrabIdx_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mShootSpeed_s{};
    // static_param at offset 0x38
    const float* mShootAng_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mBlurMax_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
