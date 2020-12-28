#include "Game/AI/Action/actionCameraEventOverwriteFar.h"

namespace uking::action {

CameraEventOverwriteFar::CameraEventOverwriteFar(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraEventOverwriteFar::~CameraEventOverwriteFar() = default;

void CameraEventOverwriteFar::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventOverwriteFar::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventOverwriteFar::loadParams_() {
    getDynamicParam2(&mFar_d, "Far");
}

}  // namespace uking::action
