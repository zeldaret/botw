#include "Game/AI/Action/actionForkSetJustAvoid.h"

namespace uking::action {

ForkSetJustAvoid::ForkSetJustAvoid(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSetJustAvoid::~ForkSetJustAvoid() = default;

bool ForkSetJustAvoid::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetJustAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSetJustAvoid::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetJustAvoid::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidAngleL_s, "JustAvoidAngleL");
    getStaticParam(&mJustAvoidAngleR_s, "JustAvoidAngleR");
    getStaticParam(&mJustAvoidDistFar_s, "JustAvoidDistFar");
    getStaticParam(&mJustAvoidDistNear_s, "JustAvoidDistNear");
    getStaticParam(&mIsAddRangeToFar_s, "IsAddRangeToFar");
    getStaticParam(&mIsAddRangeToNear_s, "IsAddRangeToNear");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mSeqBank_s, "SeqBank");
}

void ForkSetJustAvoid::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
