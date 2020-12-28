#include "Game/AI/Action/actionDieAnmDropWeapon.h"

namespace uking::action {

DieAnmDropWeapon::DieAnmDropWeapon(const InitArg& arg) : DieAnm(arg) {}

DieAnmDropWeapon::~DieAnmDropWeapon() = default;

void DieAnmDropWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    DieAnm::enter_(params);
}

void DieAnmDropWeapon::loadParams_() {
    DieAnm::loadParams_();
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
}

}  // namespace uking::action
