#include "Game/AI/Action/actionCameraMagneCatch.h"

namespace uking::action {

CameraMagneCatch::CameraMagneCatch(const InitArg& arg) : CameraLockOnBase(arg) {}

CameraMagneCatch::~CameraMagneCatch() = default;

bool CameraMagneCatch::init_(sead::Heap* heap) {
    return CameraLockOnBase::init_(heap);
}

void CameraMagneCatch::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraLockOnBase::enter_(params);
}

void CameraMagneCatch::leave_() {
    CameraLockOnBase::leave_();
}

void CameraMagneCatch::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraMagneCatch::calc_() {
    CameraLockOnBase::calc_();
}

}  // namespace uking::action
