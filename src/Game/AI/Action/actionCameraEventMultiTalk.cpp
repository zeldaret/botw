#include "Game/AI/Action/actionCameraEventMultiTalk.h"

namespace uking::action {

CameraEventMultiTalk::CameraEventMultiTalk(const InitArg& arg) : CameraEvent(arg) {}

CameraEventMultiTalk::~CameraEventMultiTalk() = default;

bool CameraEventMultiTalk::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventMultiTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventMultiTalk::leave_() {
    CameraEvent::leave_();
}

void CameraEventMultiTalk::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventMultiTalk::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
