#include "Game/AI/Action/actionForkJumpToTargetOnDownEnd.h"

namespace uking::action {

ForkJumpToTargetOnDownEnd::ForkJumpToTargetOnDownEnd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkJumpToTargetOnDownEnd::~ForkJumpToTargetOnDownEnd() = default;

bool ForkJumpToTargetOnDownEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkJumpToTargetOnDownEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkJumpToTargetOnDownEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkJumpToTargetOnDownEnd::loadParams_() {
    getStaticParam(&mAngleDir_s, "AngleDir");
    getStaticParam(&mJumpDist_s, "JumpDist");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mLimitSpeed_s, "LimitSpeed");
    getStaticParam(&mEndGrSpeed_s, "EndGrSpeed");
    getStaticParam(&mJumpMinDist_s, "JumpMinDist");
    getStaticParam(&mOnGround_s, "OnGround");
    getStaticParam(&mIsBasisByTarget_s, "IsBasisByTarget");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkJumpToTargetOnDownEnd::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
