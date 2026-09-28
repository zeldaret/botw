#include "Game/Actor/Action/actionGoronHeroDescendentJump.h"

namespace uking::action {

GoronHeroDescendentJump::GoronHeroDescendentJump(const InitArg& arg) : CurveMoveToTargetBase(arg) {}

GoronHeroDescendentJump::~GoronHeroDescendentJump() = default;

bool GoronHeroDescendentJump::init_(sead::Heap* heap) {
    return CurveMoveToTargetBase::init_(heap);
}

void GoronHeroDescendentJump::enter_(ksys::act::ai::InlineParamPack* params) {
    CurveMoveToTargetBase::enter_(params);
}

void GoronHeroDescendentJump::leave_() {
    CurveMoveToTargetBase::leave_();
}

void GoronHeroDescendentJump::loadParams_() {
    CurveMoveToTargetBase::loadParams_();
    getDynamicParam(&mIsIntoCannon_d, "IsIntoCannon");
    getDynamicParam(&mJumpTargetPos_d, "JumpTargetPos");
}

void GoronHeroDescendentJump::calc_() {
    CurveMoveToTargetBase::calc_();
}

}  // namespace uking::action
