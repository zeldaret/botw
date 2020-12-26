#include "Game/AI/Action/actionForkEmitChmFieldFromWeapon.h"

namespace uking::action {

ForkEmitChmFieldFromWeapon::ForkEmitChmFieldFromWeapon(const InitArg& arg)
    : ForkEmitChmField(arg) {}

ForkEmitChmFieldFromWeapon::~ForkEmitChmFieldFromWeapon() = default;

bool ForkEmitChmFieldFromWeapon::init_(sead::Heap* heap) {
    return ForkEmitChmField::init_(heap);
}

void ForkEmitChmFieldFromWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitChmField::enter_(params);
}

void ForkEmitChmFieldFromWeapon::leave_() {
    ForkEmitChmField::leave_();
}

void ForkEmitChmFieldFromWeapon::loadParams_() {
    ForkEmitChmField::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkEmitChmFieldFromWeapon::calc_() {
    ForkEmitChmField::calc_();
}

}  // namespace uking::action
