#include "Game/AI/Action/actionCameraRumbleStop.h"

namespace uking::action {

CameraRumbleStop::CameraRumbleStop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraRumbleStop::~CameraRumbleStop() = default;

bool CameraRumbleStop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraRumbleStop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraRumbleStop::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraRumbleStop::loadParams_() {
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

void CameraRumbleStop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
