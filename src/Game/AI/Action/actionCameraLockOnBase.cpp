#include "Game/AI/Action/actionCameraLockOnBase.h"

namespace uking::action {

CameraLockOnBase::CameraLockOnBase(const InitArg& arg) : CameraAction(arg) {}

CameraLockOnBase::~CameraLockOnBase() = default;

bool CameraLockOnBase::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraLockOnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraLockOnBase::leave_() {
    CameraAction::leave_();
}

void CameraLockOnBase::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraLockOnBase::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
