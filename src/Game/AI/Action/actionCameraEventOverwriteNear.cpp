#include "Game/AI/Action/actionCameraEventOverwriteNear.h"

namespace uking::action {

CameraEventOverwriteNear::CameraEventOverwriteNear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraEventOverwriteNear::~CameraEventOverwriteNear() = default;

bool CameraEventOverwriteNear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraEventOverwriteNear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventOverwriteNear::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventOverwriteNear::loadParams_() {
    getDynamicParam2(&mNear_d, "Near");
}

void CameraEventOverwriteNear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
