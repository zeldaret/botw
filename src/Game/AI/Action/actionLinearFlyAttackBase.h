#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LinearFlyAttackBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LinearFlyAttackBase, ksys::act::ai::Action)
public:
    explicit LinearFlyAttackBase(const InitArg& arg);
    ~LinearFlyAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const float* mAttackSpeed_s{};
    // static_param at offset 0x30
    const float* mAttackSlowDownRatio_s{};
    // static_param at offset 0x38
    const float* mTargetHeightOffset_s{};
    // static_param at offset 0x40
    const float* mThroughDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
