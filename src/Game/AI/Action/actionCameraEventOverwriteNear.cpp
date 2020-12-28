#include "Game/AI/Action/actionCameraEventOverwriteNear.h"

namespace uking::action {

CameraEventOverwriteNear::CameraEventOverwriteNear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraEventOverwriteNear::~CameraEventOverwriteNear() = default;

void CameraEventOverwriteNear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventOverwriteNear::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventOverwriteNear::loadParams_() {
    getDynamicParam2(&mNear_d, "Near");
}

}  // namespace uking::action
