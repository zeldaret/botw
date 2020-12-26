#include "Game/AI/Action/actionCameraEventTurn.h"

namespace uking::action {

CameraEventTurn::CameraEventTurn(const InitArg& arg) : CameraEvent(arg) {}

CameraEventTurn::~CameraEventTurn() = default;

bool CameraEventTurn::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventTurn::leave_() {
    CameraEvent::leave_();
}

void CameraEventTurn::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventTurn::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
