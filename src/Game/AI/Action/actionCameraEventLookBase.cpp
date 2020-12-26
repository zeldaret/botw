#include "Game/AI/Action/actionCameraEventLookBase.h"

namespace uking::action {

CameraEventLookBase::CameraEventLookBase(const InitArg& arg) : CameraEvent(arg) {}

CameraEventLookBase::~CameraEventLookBase() = default;

bool CameraEventLookBase::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventLookBase::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventLookBase::leave_() {
    CameraEvent::leave_();
}

void CameraEventLookBase::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventLookBase::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
