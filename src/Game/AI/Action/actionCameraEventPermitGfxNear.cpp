#include "Game/AI/Action/actionCameraEventPermitGfxNear.h"

namespace uking::action {

CameraEventPermitGfxNear::CameraEventPermitGfxNear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraEventPermitGfxNear::~CameraEventPermitGfxNear() = default;

bool CameraEventPermitGfxNear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraEventPermitGfxNear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraEventPermitGfxNear::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraEventPermitGfxNear::loadParams_() {}

void CameraEventPermitGfxNear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
