#include "Game/AI/Action/actionForkASTrgShootArrow.h"

namespace uking::action {

ForkASTrgShootArrow::ForkASTrgShootArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgShootArrow::~ForkASTrgShootArrow() = default;

bool ForkASTrgShootArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgShootArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgShootArrow::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgShootArrow::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsEndState_s, "IsEndState");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mOffsetRangeMin_s, "OffsetRangeMin");
    getStaticParam(&mOffsetRangeMax_s, "OffsetRangeMax");
    getStaticParam(&mOffsetRateByDist_s, "OffsetRateByDist");
    getStaticParam(&mOffsetRangeMinOutOfScreen_s, "OffsetRangeMinOutOfScreen");
    getStaticParam(&mOffsetRangeMaxOutOfScreen_s, "OffsetRangeMaxOutOfScreen");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkASTrgShootArrow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
