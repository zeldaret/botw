#include "Game/AI/Action/actionCameraEventConnectTypeSpecify.h"

namespace uking::action {

CameraEventConnectTypeSpecify::CameraEventConnectTypeSpecify(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraEventConnectTypeSpecify::~CameraEventConnectTypeSpecify() = default;

bool CameraEventConnectTypeSpecify::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraEventConnectTypeSpecify::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventConnectTypeSpecify::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventConnectTypeSpecify::loadParams_() {}

void CameraEventConnectTypeSpecify::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
