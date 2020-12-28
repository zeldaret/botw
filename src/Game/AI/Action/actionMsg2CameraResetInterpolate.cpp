#include "Game/AI/Action/actionMsg2CameraResetInterpolate.h"

namespace uking::action {

Msg2CameraResetInterpolate::Msg2CameraResetInterpolate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

void Msg2CameraResetInterpolate::loadParams_() {
    getDynamicParam2(&mInterpolateParam_d, "InterpolateParam");
}

}  // namespace uking::action
