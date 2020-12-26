#include "Game/AI/Action/actionCameraEventOverwriteFar.h"

namespace uking::action {

CameraEventOverwriteFar::CameraEventOverwriteFar(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraEventOverwriteFar::~CameraEventOverwriteFar() = default;

bool CameraEventOverwriteFar::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraEventOverwriteFar::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventOverwriteFar::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventOverwriteFar::loadParams_() {
    getDynamicParam2(&mFar_d, "Far");
}

void CameraEventOverwriteFar::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
