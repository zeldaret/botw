#pragma once

#include "Game/AI/Action/actionThrowWeapon.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrowWeaponRight : public ThrowWeapon {
    SEAD_RTTI_OVERRIDE(ThrowWeaponRight, ThrowWeapon)
public:
    explicit ThrowWeaponRight(const InitArg& arg);
    ~ThrowWeaponRight() override;

protected:
};

}  // namespace uking::action
