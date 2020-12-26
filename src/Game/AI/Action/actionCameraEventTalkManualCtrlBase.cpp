#include "Game/AI/Action/actionCameraEventTalkManualCtrlBase.h"

namespace uking::action {

CameraEventTalkManualCtrlBase::CameraEventTalkManualCtrlBase(const InitArg& arg)
    : CameraEvent(arg) {}

CameraEventTalkManualCtrlBase::~CameraEventTalkManualCtrlBase() = default;

bool CameraEventTalkManualCtrlBase::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventTalkManualCtrlBase::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventTalkManualCtrlBase::leave_() {
    CameraEvent::leave_();
}

void CameraEventTalkManualCtrlBase::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventTalkManualCtrlBase::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
