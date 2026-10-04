#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonChemicalPillarAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonChemicalPillarAttack, ksys::act::ai::Action)
public:
    explicit GanonChemicalPillarAttack(const InitArg& arg);
    ~GanonChemicalPillarAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAttackPower_s{};
    // static_param at offset 0x28
    const int* mAtMinPower_s{};
    // static_param at offset 0x30
    const int* mAttackPowerForPlayer_s{};
    // static_param at offset 0x38
    const int* mPillarNum_s{};
    // static_param at offset 0x40
    const int* mPillarInterval_s{};
    // static_param at offset 0x48
    const float* mPillarOffset_s{};
    // static_param at offset 0x50
    const float* mAppearPosDist_s{};
    // static_param at offset 0x58
    const float* mAppearPosHeight_s{};
    // static_param at offset 0x60
    const float* mIgnitionInterval_s{};
    // static_param at offset 0x68
    const float* mPileScale_s{};
    // static_param at offset 0x70
    sead::SafeString mCreateActorName_s{};
    // static_param at offset 0x80
    sead::SafeString mASName_s{};
    // static_param at offset 0x90
    sead::SafeString mWaitASName_s{};
    // static_param at offset 0xa0
    sead::SafeString mCreatePileASName_s{};
    // dynamic_param at offset 0xb0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
