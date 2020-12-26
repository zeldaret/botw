#include "Game/AI/Action/actionCameraEventPlayerHideOff.h"

namespace uking::action {

CameraEventPlayerHideOff::CameraEventPlayerHideOff(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraEventPlayerHideOff::~CameraEventPlayerHideOff() = default;

bool CameraEventPlayerHideOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraEventPlayerHideOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventPlayerHideOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventPlayerHideOff::loadParams_() {}

void CameraEventPlayerHideOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
