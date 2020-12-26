#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChemicalStayObject : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChemicalStayObject, ksys::act::ai::Action)
public:
    explicit ChemicalStayObject(const InitArg& arg);
    ~ChemicalStayObject() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtAttr_s{};
    // static_param at offset 0x28
    const float* mDeleteTime_s{};
    // static_param at offset 0x30
    const float* mCurveAng_s{};
    // static_param at offset 0x38
    const float* mReduceVelRate_s{};
    // static_param at offset 0x40
    const float* mCurveAngRandomRange_s{};
    // static_param at offset 0x48
    const float* mReduceVelRandomRange_s{};
    // static_param at offset 0x50
    const float* mSideAmplitude_s{};
    // static_param at offset 0x58
    const bool* mIsBindToGeneratedActor_s{};
    // static_param at offset 0x60
    const bool* mIsChemicalAttack_s{};
    // static_param at offset 0x68
    sead::SafeString mBindNodeName_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mBindOffset_s{};
    // map_unit_param at offset 0x80
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x88
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x90
    const int* mCreateLimit_m{};
    // map_unit_param at offset 0x98
    const float* mScaleTime_m{};
};

}  // namespace uking::action
