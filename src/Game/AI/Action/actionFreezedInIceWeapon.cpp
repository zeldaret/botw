#include "Game/AI/Action/actionFreezedInIceWeapon.h"

namespace uking::action {

FreezedInIceWeapon::FreezedInIceWeapon(const InitArg& arg) : FreezedInIce(arg) {}

FreezedInIceWeapon::~FreezedInIceWeapon() = default;

bool FreezedInIceWeapon::init_(sead::Heap* heap) {
    return FreezedInIce::init_(heap);
}

void FreezedInIceWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    FreezedInIce::enter_(params);
}

void FreezedInIceWeapon::leave_() {
    FreezedInIce::leave_();
}

void FreezedInIceWeapon::loadParams_() {
    FreezedInIce::loadParams_();
}

void FreezedInIceWeapon::calc_() {
    FreezedInIce::calc_();
}

}  // namespace uking::action
