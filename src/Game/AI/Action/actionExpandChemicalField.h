#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ExpandChemicalField : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ExpandChemicalField, ksys::act::ai::Action)
public:
    explicit ExpandChemicalField(const InitArg& arg);
    ~ExpandChemicalField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x28
    const int* mAttackAttr_m{};
    // map_unit_param at offset 0x30
    const int* mAttackType_m{};
    // map_unit_param at offset 0x38
    const int* mCutGrassType_m{};
    // map_unit_param at offset 0x40
    const int* mAttackTarget_m{};
    // map_unit_param at offset 0x48
    const int* mAttackDirType_m{};
    // map_unit_param at offset 0x50
    const float* mScaleTime_m{};
    // map_unit_param at offset 0x58
    const bool* mIsReuseActor_m{};
    // map_unit_param at offset 0x60
    const bool* mIsUseAtCollision_m{};
    // map_unit_param at offset 0x68
    sead::SafeString mXLinkKey_m{};
};

}  // namespace uking::action
