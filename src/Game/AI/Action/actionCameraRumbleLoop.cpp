#include "Game/AI/Action/actionCameraRumbleLoop.h"

namespace uking::action {

CameraRumbleLoop::CameraRumbleLoop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void CameraRumbleLoop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraRumbleLoop::loadParams_() {
    getDynamicParam2(&mPattern_d, "Pattern");
    getDynamicParam2(&mPower_d, "Power");
    getDynamicParam2(&mSideways_d, "Sideways");
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

}  // namespace uking::action
