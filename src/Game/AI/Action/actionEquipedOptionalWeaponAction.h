#pragma once

#include "Game/AI/Action/actionBindAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipedOptionalWeaponAction : public BindAction {
    SEAD_RTTI_OVERRIDE(EquipedOptionalWeaponAction, BindAction)
public:
    explicit EquipedOptionalWeaponAction(const InitArg& arg);

protected:
};

}  // namespace uking::action
