#include "Game/AI/Action/actionCameraEventPolarCoordPlayer.h"

namespace uking::action {

CameraEventPolarCoordPlayer::CameraEventPolarCoordPlayer(const InitArg& arg)
    : CameraEventPolarCoord(arg) {}

CameraEventPolarCoordPlayer::~CameraEventPolarCoordPlayer() = default;

bool CameraEventPolarCoordPlayer::init_(sead::Heap* heap) {
    return CameraEventPolarCoord::init_(heap);
}

void CameraEventPolarCoordPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventPolarCoord::enter_(params);
}

void CameraEventPolarCoordPlayer::leave_() {
    CameraEventPolarCoord::leave_();
}

void CameraEventPolarCoordPlayer::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventPolarCoordPlayer::calc_() {
    CameraEventPolarCoord::calc_();
}

}  // namespace uking::action
