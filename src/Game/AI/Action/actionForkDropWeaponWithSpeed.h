#pragma once

#include "Game/AI/Action/actionForkDropWeapon.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDropWeaponWithSpeed : public ForkDropWeapon {
    SEAD_RTTI_OVERRIDE(ForkDropWeaponWithSpeed, ForkDropWeapon)
public:
    explicit ForkDropWeaponWithSpeed(const InitArg& arg);
    ~ForkDropWeaponWithSpeed() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
