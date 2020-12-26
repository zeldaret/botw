#include "Game/AI/Action/actionCameraEventReserveConnectTime.h"

namespace uking::action {

CameraEventReserveConnectTime::CameraEventReserveConnectTime(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraEventReserveConnectTime::~CameraEventReserveConnectTime() = default;

bool CameraEventReserveConnectTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraEventReserveConnectTime::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventReserveConnectTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventReserveConnectTime::loadParams_() {
    getDynamicParam2(&mInterpolateTime_d, "InterpolateTime");
}

void CameraEventReserveConnectTime::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
