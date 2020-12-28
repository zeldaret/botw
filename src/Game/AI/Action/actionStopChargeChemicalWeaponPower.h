#pragma once

#include "Game/AI/Action/actionSetChemicalWeaponPower.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StopChargeChemicalWeaponPower : public SetChemicalWeaponPower {
    SEAD_RTTI_OVERRIDE(StopChargeChemicalWeaponPower, SetChemicalWeaponPower)
public:
    explicit StopChargeChemicalWeaponPower(const InitArg& arg);
    ~StopChargeChemicalWeaponPower() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
