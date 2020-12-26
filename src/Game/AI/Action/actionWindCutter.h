#pragma once

#include "Game/AI/Action/actionChemicalAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WindCutter : public ChemicalAttack {
    SEAD_RTTI_OVERRIDE(WindCutter, ChemicalAttack)
public:
    explicit WindCutter(const InitArg& arg);
    ~WindCutter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const int* mLevelAtkMult_s{};
    // static_param at offset 0x88
    const int* mLevelBaseScaleAdd_s{};
    // static_param at offset 0x90
    const float* mLevelRangeMult_s{};
    // static_param at offset 0x98
    const float* mLevelScaleMult_s{};
    // static_param at offset 0xa0
    const bool* mIsLevelOneScaleOne_s{};
    // map_unit_param at offset 0xa8
    const int* mAttackLevel_m{};
    // map_unit_param at offset 0xb0
    const int* mAttackDirType_m{};
    // aitree_variable at offset 0xb8
    bool* mAttackAttrEventKill_a{};
};

}  // namespace uking::action
