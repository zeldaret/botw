#include "Game/AI/Action/actionCameraEventTalkManualCtrlRet.h"

namespace uking::action {

CameraEventTalkManualCtrlRet::CameraEventTalkManualCtrlRet(const InitArg& arg)
    : CameraEventTalkManualCtrlBase(arg) {}

CameraEventTalkManualCtrlRet::~CameraEventTalkManualCtrlRet() = default;

bool CameraEventTalkManualCtrlRet::init_(sead::Heap* heap) {
    return CameraEventTalkManualCtrlBase::init_(heap);
}

void CameraEventTalkManualCtrlRet::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventTalkManualCtrlBase::enter_(params);
}

void CameraEventTalkManualCtrlRet::leave_() {
    CameraEventTalkManualCtrlBase::leave_();
}

void CameraEventTalkManualCtrlRet::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventTalkManualCtrlRet::calc_() {
    CameraEventTalkManualCtrlBase::calc_();
}

}  // namespace uking::action
