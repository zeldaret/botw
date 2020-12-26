#pragma once

#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageBase : public TakeHitImpactForce {
    SEAD_RTTI_OVERRIDE(SmallDamageBase, TakeHitImpactForce)
public:
    explicit SmallDamageBase(const InitArg& arg);
    ~SmallDamageBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mVelReduce_s{};
    // static_param at offset 0x28
    const float* mHighSpeedY_s{};
    // static_param at offset 0x30
    const float* mVelReduceY_s{};
    // static_param at offset 0x38
    const float* mHitImpactForceSmallSwordS_s{};
    // static_param at offset 0x40
    const float* mHitImpactForceSmallSwordL_s{};
    // static_param at offset 0x48
    const float* mHitImpactForceLargeSwordS_s{};
    // static_param at offset 0x50
    const float* mHitImpactForceLargeSwordL_s{};
    // static_param at offset 0x58
    const float* mHitImpactForceSpearS_s{};
    // static_param at offset 0x60
    const float* mHitImpactForceSpearL_s{};
};

}  // namespace uking::action
