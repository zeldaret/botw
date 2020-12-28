#include "Game/AI/Action/actionPlayerForkDropWeaponWithSpeed.h"

namespace uking::action {

PlayerForkDropWeaponWithSpeed::PlayerForkDropWeaponWithSpeed(const InitArg& arg)
    : ForkDropWeaponWithSpeed(arg) {}

PlayerForkDropWeaponWithSpeed::~PlayerForkDropWeaponWithSpeed() = default;

bool PlayerForkDropWeaponWithSpeed::init_(sead::Heap* heap) {
    return ForkDropWeapon::init_(heap);  // NOLINT(bugprone-parent-virtual-call)
}

void PlayerForkDropWeaponWithSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDropWeaponWithSpeed::enter_(params);
}

void PlayerForkDropWeaponWithSpeed::leave_() {
    ForkDropWeapon::leave_();  // NOLINT(bugprone-parent-virtual-call)
}

void PlayerForkDropWeaponWithSpeed::loadParams_() {
    ForkDropWeapon::loadParams_();  // NOLINT(bugprone-parent-virtual-call)
}

void PlayerForkDropWeaponWithSpeed::calc_() {
    ForkDropWeaponWithSpeed::calc_();
}

}  // namespace uking::action
