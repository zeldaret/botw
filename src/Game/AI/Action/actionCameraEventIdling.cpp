#include "Game/AI/Action/actionCameraEventIdling.h"

namespace uking::action {

CameraEventIdling::CameraEventIdling(const InitArg& arg) : CameraEvent(arg) {}

CameraEventIdling::~CameraEventIdling() = default;

bool CameraEventIdling::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventIdling::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventIdling::leave_() {
    CameraEvent::leave_();
}

void CameraEventIdling::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventIdling::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
