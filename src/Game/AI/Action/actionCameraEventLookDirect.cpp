#include "Game/AI/Action/actionCameraEventLookDirect.h"

namespace uking::action {

CameraEventLookDirect::CameraEventLookDirect(const InitArg& arg) : CameraEventLookBase(arg) {}

CameraEventLookDirect::~CameraEventLookDirect() = default;

bool CameraEventLookDirect::init_(sead::Heap* heap) {
    return CameraEventLookBase::init_(heap);
}

void CameraEventLookDirect::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventLookBase::enter_(params);
}

void CameraEventLookDirect::leave_() {
    CameraEventLookBase::leave_();
}

void CameraEventLookDirect::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventLookDirect::calc_() {
    CameraEventLookBase::calc_();
}

}  // namespace uking::action
