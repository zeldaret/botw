#pragma once

#include "Game/AI/Action/actionForkNoWeaponAttackAllTime.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkChemicalChuchuAttack : public ForkNoWeaponAttackAllTime {
    SEAD_RTTI_OVERRIDE(ForkChemicalChuchuAttack, ForkNoWeaponAttackAllTime)
public:
    explicit ForkChemicalChuchuAttack(const InitArg& arg);
    ~ForkChemicalChuchuAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const int* mLandAtkTime_s{};
    // static_param at offset 0xc8
    const float* mLandAtkRadius_s{};
};

}  // namespace uking::action
