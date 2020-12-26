#include "Game/AI/Action/actionCameraLockOnAimingAt.h"

namespace uking::action {

CameraLockOnAimingAt::CameraLockOnAimingAt(const InitArg& arg) : CameraAction(arg) {}

CameraLockOnAimingAt::~CameraLockOnAimingAt() = default;

bool CameraLockOnAimingAt::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraLockOnAimingAt::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraLockOnAimingAt::leave_() {
    CameraAction::leave_();
}

void CameraLockOnAimingAt::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraLockOnAimingAt::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
