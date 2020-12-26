#include "Game/AI/Action/actionForkAlwaysTargetVerticalRotate.h"

namespace uking::action {

ForkAlwaysTargetVerticalRotate::ForkAlwaysTargetVerticalRotate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkAlwaysTargetVerticalRotate::~ForkAlwaysTargetVerticalRotate() = default;

bool ForkAlwaysTargetVerticalRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysTargetVerticalRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAlwaysTargetVerticalRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysTargetVerticalRotate::loadParams_() {
    getStaticParam(&mRotSpdMax_s, "RotSpdMax");
    getStaticParam(&mRotSpdRatio_s, "RotSpdRatio");
    getStaticParam(&mIsUpdateTargetPos_s, "IsUpdateTargetPos");
    getStaticParam(&mIsIgnoreY_s, "IsIgnoreY");
    getStaticParam(&mOtherAxis_s, "OtherAxis");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkAlwaysTargetVerticalRotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
