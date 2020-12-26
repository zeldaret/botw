#include "Game/AI/Action/actionCameraLockOn.h"

namespace uking::action {

CameraLockOn::CameraLockOn(const InitArg& arg) : CameraLockOnBase(arg) {}

CameraLockOn::~CameraLockOn() = default;

bool CameraLockOn::init_(sead::Heap* heap) {
    return CameraLockOnBase::init_(heap);
}

void CameraLockOn::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraLockOnBase::enter_(params);
}

void CameraLockOn::leave_() {
    CameraLockOnBase::leave_();
}

void CameraLockOn::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraLockOn::calc_() {
    CameraLockOnBase::calc_();
}

}  // namespace uking::action
