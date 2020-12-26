#include "Game/AI/Action/actionCameraKeep.h"

namespace uking::action {

CameraKeep::CameraKeep(const InitArg& arg) : CameraAction(arg) {}

CameraKeep::~CameraKeep() = default;

bool CameraKeep::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraKeep::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraKeep::leave_() {
    CameraAction::leave_();
}

void CameraKeep::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraKeep::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
