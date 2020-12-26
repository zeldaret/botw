#include "Game/AI/Action/actionCameraRumbleStopWithDamping.h"

namespace uking::action {

CameraRumbleStopWithDamping::CameraRumbleStopWithDamping(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraRumbleStopWithDamping::~CameraRumbleStopWithDamping() = default;

bool CameraRumbleStopWithDamping::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraRumbleStopWithDamping::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraRumbleStopWithDamping::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraRumbleStopWithDamping::loadParams_() {
    getDynamicParam2(&mDampingTime_d, "DampingTime");
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

void CameraRumbleStopWithDamping::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
