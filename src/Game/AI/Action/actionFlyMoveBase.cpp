#include "Game/AI/Action/actionFlyMoveBase.h"

namespace uking::action {

FlyMoveBase::FlyMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FlyMoveBase::~FlyMoveBase() = default;

bool FlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FlyMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void FlyMoveBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mHorizontalFinRadius_s, "HorizontalFinRadius");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mVerticalFinLength_s, "VerticalFinLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void FlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
