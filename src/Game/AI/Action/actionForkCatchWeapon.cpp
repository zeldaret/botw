#include "Game/AI/Action/actionForkCatchWeapon.h"

namespace uking::action {

ForkCatchWeapon::ForkCatchWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkCatchWeapon::~ForkCatchWeapon() = default;

bool ForkCatchWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkCatchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkCatchWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkCatchWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mIsNoGrabSuccess_s, "IsNoGrabSuccess");
}

void ForkCatchWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
