#include "Game/AI/Action/actionCameraEvent.h"

namespace uking::action {

CameraEvent::CameraEvent(const InitArg& arg) : CameraAction(arg) {}

CameraEvent::~CameraEvent() = default;

bool CameraEvent::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraEvent::leave_() {
    CameraAction::leave_();
}

void CameraEvent::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEvent::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
