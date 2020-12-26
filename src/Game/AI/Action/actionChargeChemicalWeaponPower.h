#pragma once

#include "Game/AI/Action/actionSetChemicalWeaponPower.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChargeChemicalWeaponPower : public SetChemicalWeaponPower {
    SEAD_RTTI_OVERRIDE(ChargeChemicalWeaponPower, SetChemicalWeaponPower)
public:
    explicit ChargeChemicalWeaponPower(const InitArg& arg);
    ~ChargeChemicalWeaponPower() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
