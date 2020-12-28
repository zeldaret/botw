#include "Game/AI/Action/actionCameraRumbleStopWithDamping.h"

namespace uking::action {

CameraRumbleStopWithDamping::CameraRumbleStopWithDamping(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

void CameraRumbleStopWithDamping::loadParams_() {
    getDynamicParam2(&mDampingTime_d, "DampingTime");
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

}  // namespace uking::action
