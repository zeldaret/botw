#include "Game/AI/Action/actionLynelDrawWeapon.h"

namespace uking::action {

LynelDrawWeapon::LynelDrawWeapon(const InitArg& arg) : ForkLynelDrawWeaponASPlay(arg) {}

LynelDrawWeapon::~LynelDrawWeapon() = default;

bool LynelDrawWeapon::init_(sead::Heap* heap) {
    return ForkLynelDrawWeaponASPlay::init_(heap);
}

void LynelDrawWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkLynelDrawWeaponASPlay::enter_(params);
}

void LynelDrawWeapon::leave_() {
    ForkLynelDrawWeaponASPlay::leave_();
}

void LynelDrawWeapon::loadParams_() {
    ForkLynelDrawWeaponASPlay::loadParams_();
}

void LynelDrawWeapon::calc_() {
    ForkLynelDrawWeaponASPlay::calc_();
}

}  // namespace uking::action
