#pragma once

#include "Game/AI/Action/actionThrowWeapon.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrowWeaponRight : public ThrowWeapon {
    SEAD_RTTI_OVERRIDE(ThrowWeaponRight, ThrowWeapon)
public:
    explicit ThrowWeaponRight(const InitArg& arg);
    ~ThrowWeaponRight() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const float* mSpeedMin_s{};
    // static_param at offset 0x40
    const float* mSpeedMax_s{};
    // static_param at offset 0x48
    const float* mThrowAng_s{};
    // static_param at offset 0x50
    const float* mThrowBoomerangAng_s{};
    // static_param at offset 0x58
    const float* mThrowBoomerangSpeedMax_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x68
    const bool* mIsForceDead_s{};
};

}  // namespace uking::action
