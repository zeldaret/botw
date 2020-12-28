#include "Game/AI/Action/actionFreezedInIceWeapon.h"

namespace uking::action {

FreezedInIceWeapon::FreezedInIceWeapon(const InitArg& arg) : FreezedInIce(arg) {}

FreezedInIceWeapon::~FreezedInIceWeapon() = default;

void FreezedInIceWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    FreezedInIce::enter_(params);
}

void FreezedInIceWeapon::leave_() {
    FreezedInIce::leave_();
}

void FreezedInIceWeapon::loadParams_() {
    FreezedInIce::loadParams_();
}

}  // namespace uking::action
