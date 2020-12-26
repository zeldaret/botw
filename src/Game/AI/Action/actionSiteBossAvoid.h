#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossAvoid : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossAvoid, ksys::act::ai::Action)
public:
    explicit SiteBossAvoid(const InitArg& arg);
    ~SiteBossAvoid() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAvoidEndTime_s{};
    // static_param at offset 0x28
    const float* mAvoidMoveSpeed_s{};
    // dynamic_param at offset 0x30
    float* mAvoidDist_d{};
    // dynamic_param at offset 0x38
    bool* mIsAvoidHorizon_d{};
    // dynamic_param at offset 0x40
    bool* mIsSlerp_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mAvoidVec_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mPlayerPos_d{};
};

}  // namespace uking::action
