#pragma once

#include "Game/AI/Action/actionGanonWeaponNearAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonAttackWithEmitChemical : public GanonWeaponNearAttack {
    SEAD_RTTI_OVERRIDE(GanonAttackWithEmitChemical, GanonWeaponNearAttack)
public:
    explicit GanonAttackWithEmitChemical(const InitArg& arg);
    ~GanonAttackWithEmitChemical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const int* mEmitNum_s{};
    // static_param at offset 0xb0
    const int* mEmitInterval_s{};
    // static_param at offset 0xb8
    const int* mEmitAttackPower_s{};
    // static_param at offset 0xc0
    const int* mEmitMinDamage_s{};
    // static_param at offset 0xc8
    const int* mChildCreateLimit_s{};
    // static_param at offset 0xd0
    const float* mEmitOffsetFromParent_s{};
    // static_param at offset 0xd8
    const float* mEmitIntervalDist_s{};
    // static_param at offset 0xe0
    const float* mEmitIntervalRotate_s{};
    // static_param at offset 0xe8
    const float* mEmitScale_s{};
    // static_param at offset 0xf0
    const float* mEmitMaxScale_s{};
    // static_param at offset 0xf8
    const float* mScaleTime_s{};
    // static_param at offset 0x100
    const float* mEmitStartFrame_s{};
    // static_param at offset 0x108
    const float* mEmitAngleFromParent_s{};
    // static_param at offset 0x110
    const float* mEmitActorSpeedRotate_s{};
    // static_param at offset 0x118
    sead::SafeString mEmitActorName_s{};
    // static_param at offset 0x128
    sead::SafeString mEmitBaseBoneName_s{};
    // static_param at offset 0x138
    sead::SafeString mEmitPartsName_s{};
    // static_param at offset 0x148
    sead::SafeString mCallSEKeyAtAtOn_s{};
    // static_param at offset 0x158
    const sead::Vector3f* mEmitActorSpeed_s{};
    // static_param at offset 0x160
    const sead::Vector3f* mEmitBoneRotateOffset_s{};
};

}  // namespace uking::action
