#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseNotRidden : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseNotRidden, ksys::act::ai::Ai)
public:
    explicit HorseNotRidden(const InitArg& arg);
    ~HorseNotRidden() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mEscapeCountThreshold_s{};
    // static_param at offset 0x40
    const float* mNearHorseAssociationDistance_s{};
    // static_param at offset 0x48
    const float* mEscapeDelayFramesMin_s{};
    // static_param at offset 0x50
    const float* mEscapeDelayFramesMax_s{};
    // static_param at offset 0x58
    const float* mCallDelayFrames_s{};
    // static_param at offset 0x60
    const float* mAttackFrontDistance_s{};
    // static_param at offset 0x68
    const float* mAttackFrontAngleCos_s{};
    // static_param at offset 0x70
    const float* mAttackBackDistance_s{};
    // static_param at offset 0x78
    const float* mAttackBackAngleCos_s{};
    // static_param at offset 0x80
    const float* mAttackDefinitelyDistance_s{};
    // static_param at offset 0x88
    const float* mAttackIntervalFrames_s{};
    // static_param at offset 0x90
    const float* mMoveAttackCLOSDistanceByRadius_s{};
    // static_param at offset 0x98
    const float* mCarriedItemCosThresholdForEat_s{};
    // static_param at offset 0xa0
    const float* mStaggerVelocityThreshold_s{};
    // static_param at offset 0xa8
    const sead::Vector3f* mCarriedItemPosRTYOffset_s{};
    // static_param at offset 0xb0
    const sead::Vector3f* mCarriedItemPosRTYWidth_s{};
    // dynamic_param at offset 0xb8
    int* mChildSelectAtFirst_d{};
};

}  // namespace uking::ai
