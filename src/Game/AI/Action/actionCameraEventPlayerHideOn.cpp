#include "Game/AI/Action/actionCameraEventPlayerHideOn.h"

namespace uking::action {

CameraEventPlayerHideOn::CameraEventPlayerHideOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraEventPlayerHideOn::~CameraEventPlayerHideOn() = default;

bool CameraEventPlayerHideOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraEventPlayerHideOn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventPlayerHideOn::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventPlayerHideOn::loadParams_() {}

void CameraEventPlayerHideOn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
