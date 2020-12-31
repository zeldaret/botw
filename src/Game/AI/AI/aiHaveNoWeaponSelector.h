#pragma once

#include "Game/AI/AI/aiEquipHaveSelector.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HaveNoWeaponSelector : public EquipHaveSelector {
    SEAD_RTTI_OVERRIDE(HaveNoWeaponSelector, EquipHaveSelector)
public:
    explicit HaveNoWeaponSelector(const InitArg& arg);
    ~HaveNoWeaponSelector() override;

protected:
};

}  // namespace uking::ai
