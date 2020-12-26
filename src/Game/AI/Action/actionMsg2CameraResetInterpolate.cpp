#include "Game/AI/Action/actionMsg2CameraResetInterpolate.h"

namespace uking::action {

Msg2CameraResetInterpolate::Msg2CameraResetInterpolate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

Msg2CameraResetInterpolate::~Msg2CameraResetInterpolate() = default;

bool Msg2CameraResetInterpolate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Msg2CameraResetInterpolate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Msg2CameraResetInterpolate::leave_() {
    ksys::act::ai::Action::leave_();
}

void Msg2CameraResetInterpolate::loadParams_() {
    getDynamicParam2(&mInterpolateParam_d, "InterpolateParam");
}

void Msg2CameraResetInterpolate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
