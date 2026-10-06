#pragma once

#include "Game/Actor/Action/actionChemicalAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChemicalElectricWaterBall : public ChemicalAttack {
    SEAD_RTTI_OVERRIDE(ChemicalElectricWaterBall, ChemicalAttack)
public:
    explicit ChemicalElectricWaterBall(const InitArg& arg);
    ~ChemicalElectricWaterBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const int* mDeleteTime_s{};
    // static_param at offset 0x98
    const float* mTargetScale_s{};
    // static_param at offset 0xa0
    const bool* mScaleKeep_s{};
    // aitree_variable at offset 0xa8
    void* mChemicalBulletBindActor_a{};
};

}  // namespace uking::action
