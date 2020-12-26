#include "Game/AI/Action/actionCameraEventTalkManualCtrl.h"

namespace uking::action {

CameraEventTalkManualCtrl::CameraEventTalkManualCtrl(const InitArg& arg)
    : CameraEventTalkManualCtrlBase(arg) {}

CameraEventTalkManualCtrl::~CameraEventTalkManualCtrl() = default;

bool CameraEventTalkManualCtrl::init_(sead::Heap* heap) {
    return CameraEventTalkManualCtrlBase::init_(heap);
}

void CameraEventTalkManualCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventTalkManualCtrlBase::enter_(params);
}

void CameraEventTalkManualCtrl::leave_() {
    CameraEventTalkManualCtrlBase::leave_();
}

void CameraEventTalkManualCtrl::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventTalkManualCtrl::calc_() {
    CameraEventTalkManualCtrlBase::calc_();
}

}  // namespace uking::action
