#include "Game/AI/Action/actionCameraEventLook.h"

namespace uking::action {

CameraEventLook::CameraEventLook(const InitArg& arg) : CameraEventLookBase(arg) {}

CameraEventLook::~CameraEventLook() = default;

bool CameraEventLook::init_(sead::Heap* heap) {
    return CameraEventLookBase::init_(heap);
}

void CameraEventLook::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventLookBase::enter_(params);
}

void CameraEventLook::leave_() {
    CameraEventLookBase::leave_();
}

void CameraEventLook::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventLook::calc_() {
    CameraEventLookBase::calc_();
}

}  // namespace uking::action
