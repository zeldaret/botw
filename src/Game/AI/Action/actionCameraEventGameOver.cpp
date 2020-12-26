#include "Game/AI/Action/actionCameraEventGameOver.h"

namespace uking::action {

CameraEventGameOver::CameraEventGameOver(const InitArg& arg) : CameraEvent(arg) {}

CameraEventGameOver::~CameraEventGameOver() = default;

bool CameraEventGameOver::init_(sead::Heap* heap) {
    return CameraEvent::init_(heap);
}

void CameraEventGameOver::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEvent::enter_(params);
}

void CameraEventGameOver::leave_() {
    CameraEvent::leave_();
}

void CameraEventGameOver::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventGameOver::calc_() {
    CameraEvent::calc_();
}

}  // namespace uking::action
