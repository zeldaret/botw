#include "Game/AI/Action/actionCameraEventPolarCoord.h"

namespace uking::action {

CameraEventPolarCoord::CameraEventPolarCoord(const InitArg& arg) : CameraEvent(arg) {}

CameraEventPolarCoord::~CameraEventPolarCoord() = default;

bool CameraEventPolarCoord::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventPolarCoord::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventPolarCoord::leave_() {
    CameraEvent::leave_();
}

void CameraEventPolarCoord::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventPolarCoord::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
