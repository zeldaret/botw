#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardBreak : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GuardBreak, ksys::act::ai::Action)
public:
    explicit GuardBreak(const InitArg& arg);
    ~GuardBreak() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mKnockBackTime_s{};
    // static_param at offset 0x28
    const int* mDropIdx_s{};
    // static_param at offset 0x30
    const float* mHitImpactForce_s{};
    // static_param at offset 0x38
    const float* mVelReduce_s{};
    // static_param at offset 0x40
    const float* mWeaponVel_s{};
    // static_param at offset 0x48
    const float* mWeaponVelY_s{};
};

}  // namespace uking::action
