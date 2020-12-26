#include "Game/AI/Action/actionCameraEventTalk.h"

namespace uking::action {

CameraEventTalk::CameraEventTalk(const InitArg& arg) : CameraEvent(arg) {}

CameraEventTalk::~CameraEventTalk() = default;

bool CameraEventTalk::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventTalk::leave_() {
    CameraEvent::leave_();
}

void CameraEventTalk::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventTalk::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
