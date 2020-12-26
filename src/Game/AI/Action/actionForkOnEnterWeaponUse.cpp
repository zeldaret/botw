#include "Game/AI/Action/actionForkOnEnterWeaponUse.h"

namespace uking::action {

ForkOnEnterWeaponUse::ForkOnEnterWeaponUse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkOnEnterWeaponUse::~ForkOnEnterWeaponUse() = default;

bool ForkOnEnterWeaponUse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnEnterWeaponUse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkOnEnterWeaponUse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOnEnterWeaponUse::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void ForkOnEnterWeaponUse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
