#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossShieldBashAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossShieldBashAttack, ksys::act::ai::Action)
public:
    explicit SiteBossShieldBashAttack(const InitArg& arg);
    ~SiteBossShieldBashAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const float* mInitSpeed_s{};
    // static_param at offset 0x30
    const float* mKeepDist_s{};
    // static_param at offset 0x38
    const float* mMoveSpeed_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
