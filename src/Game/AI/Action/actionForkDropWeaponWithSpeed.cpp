#include "Game/AI/Action/actionForkDropWeaponWithSpeed.h"

namespace uking::action {

ForkDropWeaponWithSpeed::ForkDropWeaponWithSpeed(const InitArg& arg) : ForkDropWeapon(arg) {}

ForkDropWeaponWithSpeed::~ForkDropWeaponWithSpeed() = default;

void ForkDropWeaponWithSpeed::calc_() {
    ForkDropWeapon::calc_();
}

}  // namespace uking::action
