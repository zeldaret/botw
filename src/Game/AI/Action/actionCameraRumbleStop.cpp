#include "Game/AI/Action/actionCameraRumbleStop.h"

namespace uking::action {

CameraRumbleStop::CameraRumbleStop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void CameraRumbleStop::loadParams_() {
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

}  // namespace uking::action
