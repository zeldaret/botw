#include "Game/AI/Action/actionForkOnEnterDropWeaponWithSpeed.h"

namespace uking::action {

ForkOnEnterDropWeaponWithSpeed::ForkOnEnterDropWeaponWithSpeed(const InitArg& arg)
    : ForkDropWeapon(arg) {}

ForkOnEnterDropWeaponWithSpeed::~ForkOnEnterDropWeaponWithSpeed() = default;

bool ForkOnEnterDropWeaponWithSpeed::init_(sead::Heap* heap) {
    return ForkDropWeapon::init_(heap);
}

void ForkOnEnterDropWeaponWithSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDropWeapon::enter_(params);
}

void ForkOnEnterDropWeaponWithSpeed::leave_() {
    ForkDropWeapon::leave_();
}

void ForkOnEnterDropWeaponWithSpeed::loadParams_() {
    ForkDropWeapon::loadParams_();
}

void ForkOnEnterDropWeaponWithSpeed::calc_() {
    ForkDropWeapon::calc_();
}

}  // namespace uking::action
