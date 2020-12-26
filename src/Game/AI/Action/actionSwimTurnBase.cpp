#include "Game/AI/Action/actionSwimTurnBase.h"

namespace uking::action {

SwimTurnBase::SwimTurnBase(const InitArg& arg) : SwimRotateBase(arg) {}

SwimTurnBase::~SwimTurnBase() = default;

bool SwimTurnBase::init_(sead::Heap* heap) {
    return SwimRotateBase::init_(heap);
}

void SwimTurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimRotateBase::enter_(params);
}

void SwimTurnBase::leave_() {
    SwimRotateBase::leave_();
}

void SwimTurnBase::loadParams_() {
    SwimRotateBase::loadParams_();
    getStaticParam(&mFinRotate_s, "FinRotate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SwimTurnBase::calc_() {
    SwimRotateBase::calc_();
}

}  // namespace uking::action
