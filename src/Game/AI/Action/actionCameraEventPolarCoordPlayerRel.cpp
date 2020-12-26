#include "Game/AI/Action/actionCameraEventPolarCoordPlayerRel.h"

namespace uking::action {

CameraEventPolarCoordPlayerRel::CameraEventPolarCoordPlayerRel(const InitArg& arg)
    : CameraEventPolarCoordPlayer(arg) {}

CameraEventPolarCoordPlayerRel::~CameraEventPolarCoordPlayerRel() = default;

bool CameraEventPolarCoordPlayerRel::init_(sead::Heap* heap) {
    return CameraEventPolarCoordPlayer::init_(heap);
}

void CameraEventPolarCoordPlayerRel::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraEventPolarCoordPlayer::enter_(params);
}

void CameraEventPolarCoordPlayerRel::leave_() {
    CameraEventPolarCoordPlayer::leave_();
}

void CameraEventPolarCoordPlayerRel::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraEventPolarCoordPlayerRel::calc_() {
    CameraEventPolarCoordPlayer::calc_();
}

}  // namespace uking::action
