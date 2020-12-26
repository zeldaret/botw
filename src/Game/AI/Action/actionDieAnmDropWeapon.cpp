#include "Game/AI/Action/actionDieAnmDropWeapon.h"

namespace uking::action {

DieAnmDropWeapon::DieAnmDropWeapon(const InitArg& arg) : DieAnm(arg) {}

DieAnmDropWeapon::~DieAnmDropWeapon() = default;

bool DieAnmDropWeapon::init_(sead::Heap* heap) {
    return DieAnm::init_(heap);
}

void DieAnmDropWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    DieAnm::enter_(params);
}

void DieAnmDropWeapon::leave_() {
    DieAnm::leave_();
}

void DieAnmDropWeapon::loadParams_() {
    DieAnm::loadParams_();
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
}

void DieAnmDropWeapon::calc_() {
    DieAnm::calc_();
}

}  // namespace uking::action
