#include "Game/Actor/Camera/Action/actionCameraEventReserveConnectTime.h"

namespace uking::action {

CameraEventReserveConnectTime::CameraEventReserveConnectTime(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraEventReserveConnectTime::~CameraEventReserveConnectTime() = default;

void CameraEventReserveConnectTime::loadParams_() {
    getDynamicParam_2(&mInterpolateTime_d, "InterpolateTime");
}

}  // namespace uking::action
