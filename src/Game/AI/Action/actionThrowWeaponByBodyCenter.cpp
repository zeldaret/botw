#include "Game/AI/Action/actionThrowWeaponByBodyCenter.h"

namespace uking::action {

ThrowWeaponByBodyCenter::ThrowWeaponByBodyCenter(const InitArg& arg) : ThrowWeapon(arg) {}

ThrowWeaponByBodyCenter::~ThrowWeaponByBodyCenter() = default;

bool ThrowWeaponByBodyCenter::init_(sead::Heap* heap) {
    return ThrowWeapon::init_(heap);
}

void ThrowWeaponByBodyCenter::enter_(ksys::act::ai::InlineParamPack* params) {
    ThrowWeapon::enter_(params);
}

void ThrowWeaponByBodyCenter::leave_() {
    ThrowWeapon::leave_();
}

void ThrowWeaponByBodyCenter::loadParams_() {
    ThrowWeapon::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ThrowWeaponByBodyCenter::calc_() {
    ThrowWeapon::calc_();
}

}  // namespace uking::action
