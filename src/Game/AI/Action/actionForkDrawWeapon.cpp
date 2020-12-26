#include "Game/AI/Action/actionForkDrawWeapon.h"

namespace uking::action {

ForkDrawWeapon::ForkDrawWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDrawWeapon::~ForkDrawWeapon() = default;

bool ForkDrawWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDrawWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkDrawWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkDrawWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkDrawWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
