#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideChargeAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRideChargeAttack, ksys::act::ai::Ai)
public:
    explicit HorseRideChargeAttack(const InitArg& arg);
    ~HorseRideChargeAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mUpperBodyASSlot_s{};
    // static_param at offset 0x40
    const int* mLowerBodyASSlot_s{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const float* mAttackableAngle_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
