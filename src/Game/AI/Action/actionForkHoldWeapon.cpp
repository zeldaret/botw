#include "Game/AI/Action/actionForkHoldWeapon.h"

namespace uking::action {

ForkHoldWeapon::ForkHoldWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkHoldWeapon::~ForkHoldWeapon() = default;

bool ForkHoldWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkHoldWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkHoldWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkHoldWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkHoldWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
