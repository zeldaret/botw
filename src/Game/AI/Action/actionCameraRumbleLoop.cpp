#include "Game/AI/Action/actionCameraRumbleLoop.h"

namespace uking::action {

CameraRumbleLoop::CameraRumbleLoop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraRumbleLoop::~CameraRumbleLoop() = default;

bool CameraRumbleLoop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraRumbleLoop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraRumbleLoop::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraRumbleLoop::loadParams_() {
    getDynamicParam2(&mPattern_d, "Pattern");
    getDynamicParam2(&mPower_d, "Power");
    getDynamicParam2(&mSideways_d, "Sideways");
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

void CameraRumbleLoop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
