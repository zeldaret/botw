#include "Game/AI/Action/actionCameraEventAnimBase.h"

namespace uking::action {

CameraEventAnimBase::CameraEventAnimBase(const InitArg& arg) : CameraEvent(arg) {}

CameraEventAnimBase::~CameraEventAnimBase() = default;

bool CameraEventAnimBase::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventAnimBase::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventAnimBase::leave_() {
    CameraEvent::leave_();
}

void CameraEventAnimBase::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventAnimBase::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
