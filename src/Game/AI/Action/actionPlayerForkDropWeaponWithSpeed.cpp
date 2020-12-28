#include "Game/AI/Action/actionPlayerForkDropWeaponWithSpeed.h"

namespace uking::action {

PlayerForkDropWeaponWithSpeed::PlayerForkDropWeaponWithSpeed(const InitArg& arg)
    : ForkDropWeaponWithSpeed(arg) {}

PlayerForkDropWeaponWithSpeed::~PlayerForkDropWeaponWithSpeed() = default;

bool PlayerForkDropWeaponWithSpeed::init_(sead::Heap* heap) {
    return ForkDropWeaponWithSpeed::init_(heap);
}

void PlayerForkDropWeaponWithSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDropWeaponWithSpeed::enter_(params);
}

void PlayerForkDropWeaponWithSpeed::leave_() {
    ForkDropWeaponWithSpeed::leave_();
}

void PlayerForkDropWeaponWithSpeed::loadParams_() {
    ForkDropWeapon::loadParams_();
}

void PlayerForkDropWeaponWithSpeed::calc_() {
    ForkDropWeaponWithSpeed::calc_();
}

}  // namespace uking::action
