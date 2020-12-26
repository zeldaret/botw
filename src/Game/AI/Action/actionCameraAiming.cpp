#include "Game/AI/Action/actionCameraAiming.h"

namespace uking::action {

CameraAiming::CameraAiming(const InitArg& arg) : CameraAction(arg) {}

CameraAiming::~CameraAiming() = default;

bool CameraAiming::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraAiming::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraAiming::leave_() {
    CameraAction::leave_();
}

void CameraAiming::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraAiming::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
