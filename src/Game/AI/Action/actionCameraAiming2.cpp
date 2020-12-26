#include "Game/AI/Action/actionCameraAiming2.h"

namespace uking::action {

CameraAiming2::CameraAiming2(const InitArg& arg) : CameraAction(arg) {}

CameraAiming2::~CameraAiming2() = default;

bool CameraAiming2::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraAiming2::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraAiming2::leave_() {
    CameraAction::leave_();
}

void CameraAiming2::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraAiming2::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
