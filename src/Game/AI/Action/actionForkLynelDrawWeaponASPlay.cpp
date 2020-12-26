#include "Game/AI/Action/actionForkLynelDrawWeaponASPlay.h"

namespace uking::action {

ForkLynelDrawWeaponASPlay::ForkLynelDrawWeaponASPlay(const InitArg& arg)
    : ForkLynelDrawWeapon(arg) {}

ForkLynelDrawWeaponASPlay::~ForkLynelDrawWeaponASPlay() = default;

bool ForkLynelDrawWeaponASPlay::init_(sead::Heap* heap) {
    return ForkLynelDrawWeapon::init_(heap);
}

void ForkLynelDrawWeaponASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkLynelDrawWeapon::enter_(params);
}

void ForkLynelDrawWeaponASPlay::leave_() {
    ForkLynelDrawWeapon::leave_();
}

void ForkLynelDrawWeaponASPlay::loadParams_() {
    ForkLynelDrawWeapon::loadParams_();
}

void ForkLynelDrawWeaponASPlay::calc_() {
    ForkLynelDrawWeapon::calc_();
}

}  // namespace uking::action
