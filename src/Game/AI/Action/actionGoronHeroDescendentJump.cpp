#include "Game/AI/Action/actionGoronHeroDescendentJump.h"

namespace uking::action {

GoronHeroDescendentJump::GoronHeroDescendentJump(const InitArg& arg) : MoveToTargetCurveBase(arg) {}

GoronHeroDescendentJump::~GoronHeroDescendentJump() = default;

bool GoronHeroDescendentJump::init_(sead::Heap* heap) {
    return MoveToTargetCurveBase::init_(heap);
}

void GoronHeroDescendentJump::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveToTargetCurveBase::enter_(params);
}

void GoronHeroDescendentJump::leave_() {
    MoveToTargetCurveBase::leave_();
}

void GoronHeroDescendentJump::loadParams_() {
    MoveToTargetCurveBase::loadParams_();
    getDynamicParam(&mIsIntoCannon_d, "IsIntoCannon");
    getDynamicParam(&mJumpTargetPos_d, "JumpTargetPos");
}

void GoronHeroDescendentJump::calc_() {
    MoveToTargetCurveBase::calc_();
}

}  // namespace uking::action
