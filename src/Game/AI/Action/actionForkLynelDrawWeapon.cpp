#include "Game/AI/Action/actionForkLynelDrawWeapon.h"

namespace uking::action {

ForkLynelDrawWeapon::ForkLynelDrawWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkLynelDrawWeapon::~ForkLynelDrawWeapon() = default;

bool ForkLynelDrawWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkLynelDrawWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkLynelDrawWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkLynelDrawWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx0_s, "WeaponIdx0");
    getStaticParam(&mWeaponIdx1_s, "WeaponIdx1");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mASWeaponIdx_s, "ASWeaponIdx");
    getStaticParam(&mASName_s, "ASName");
}

void ForkLynelDrawWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
