#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CreateGanonChemicalPillar : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CreateGanonChemicalPillar, ksys::act::ai::Action)
public:
    explicit CreateGanonChemicalPillar(const InitArg& arg);
    ~CreateGanonChemicalPillar() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAttackPower_s{};
    // static_param at offset 0x28
    const int* mAtMinDamage_s{};
    // static_param at offset 0x30
    const float* mScaleTime_s{};
    // static_param at offset 0x38
    const float* mMaxScale_s{};
    // static_param at offset 0x40
    sead::SafeString mCreateActorName_s{};
    // map_unit_param at offset 0x50
    const int* mAddAtkPower_m{};
};

}  // namespace uking::action
