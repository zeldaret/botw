#pragma once

#include "Game/AI/Action/actionForkNoWeaponAttackAllTime.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNoWeaponAttackAllTimeMinSet : public ForkNoWeaponAttackAllTime {
    SEAD_RTTI_OVERRIDE(ForkNoWeaponAttackAllTimeMinSet, ForkNoWeaponAttackAllTime)
public:
    explicit ForkNoWeaponAttackAllTimeMinSet(const InitArg& arg);
    ~ForkNoWeaponAttackAllTimeMinSet() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const int* mMinDamage_s{};
};

}  // namespace uking::action
