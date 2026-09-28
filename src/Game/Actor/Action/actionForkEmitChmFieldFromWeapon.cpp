#include "Game/Actor/Action/actionForkEmitChmFieldFromWeapon.h"

namespace uking::action {

ForkEmitChmFieldFromWeapon::ForkEmitChmFieldFromWeapon(const InitArg& arg)
    : ForkTrgEmitChmFieldBase(arg) {}

ForkEmitChmFieldFromWeapon::~ForkEmitChmFieldFromWeapon() = default;

bool ForkEmitChmFieldFromWeapon::init_(sead::Heap* heap) {
    return ForkTrgEmitChmFieldBase::init_(heap);
}

void ForkEmitChmFieldFromWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTrgEmitChmFieldBase::enter_(params);
}

void ForkEmitChmFieldFromWeapon::leave_() {
    ForkTrgEmitChmFieldBase::leave_();
}

void ForkEmitChmFieldFromWeapon::loadParams_() {
    ForkTrgEmitChmFieldBase::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkEmitChmFieldFromWeapon::calc_() {
    ForkTrgEmitChmFieldBase::calc_();
}

}  // namespace uking::action
