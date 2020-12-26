#pragma once

#include "Game/AI/Action/actionForkWeaponAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelSpinAttack : public ForkWeaponAttack {
    SEAD_RTTI_OVERRIDE(LynelSpinAttack, ForkWeaponAttack)
public:
    explicit LynelSpinAttack(const InitArg& arg);
    ~LynelSpinAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const int* mMinLoopTime_s{};
    // static_param at offset 0x80
    const float* mLoopEndAngle_s{};
    // static_param at offset 0x88
    sead::SafeString mStartASName_s{};
    // static_param at offset 0x98
    sead::SafeString mLoopASName_s{};
    // static_param at offset 0xa8
    sead::SafeString mEndASName_s{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
