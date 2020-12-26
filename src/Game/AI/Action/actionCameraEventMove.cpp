#include "Game/AI/Action/actionCameraEventMove.h"

namespace uking::action {

CameraEventMove::CameraEventMove(const InitArg& arg) : CameraEvent(arg) {}

CameraEventMove::~CameraEventMove() = default;

bool CameraEventMove::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventMove::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventMove::leave_() {
    CameraEvent::leave_();
}

void CameraEventMove::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventMove::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
