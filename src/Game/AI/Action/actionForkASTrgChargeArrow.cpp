#include "Game/AI/Action/actionForkASTrgChargeArrow.h"

namespace uking::action {

ForkASTrgChargeArrow::ForkASTrgChargeArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgChargeArrow::~ForkASTrgChargeArrow() = default;

bool ForkASTrgChargeArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgChargeArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgChargeArrow::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgChargeArrow::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsEndState_s, "IsEndState");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkASTrgChargeArrow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
