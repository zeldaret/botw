#include "Game/AI/Action/actionCameraEventMovePosBase.h"

namespace uking::action {

CameraEventMovePosBase::CameraEventMovePosBase(const InitArg& arg) : CameraEvent(arg) {}

CameraEventMovePosBase::~CameraEventMovePosBase() = default;

bool CameraEventMovePosBase::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventMovePosBase::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventMovePosBase::leave_() {
    CameraEvent::leave_();
}

void CameraEventMovePosBase::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventMovePosBase::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
