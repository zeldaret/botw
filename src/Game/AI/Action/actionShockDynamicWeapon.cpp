#include "Game/AI/Action/actionShockDynamicWeapon.h"

namespace uking::action {

ShockDynamicWeapon::ShockDynamicWeapon(const InitArg& arg) : Shock(arg) {}

ShockDynamicWeapon::~ShockDynamicWeapon() = default;

void ShockDynamicWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    Shock::enter_(params);
}

void ShockDynamicWeapon::leave_() {
    Shock::leave_();
}

void ShockDynamicWeapon::loadParams_() {
    Shock::loadParams_();
    getDynamicParam(&mDropWeapon_d, "DropWeapon");
    getDynamicParam(&mDropDir_d, "DropDir");
}

void ShockDynamicWeapon::calc_() {
    Shock::calc_();
}

}  // namespace uking::action
