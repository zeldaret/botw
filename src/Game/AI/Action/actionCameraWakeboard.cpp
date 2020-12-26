#include "Game/AI/Action/actionCameraWakeboard.h"

namespace uking::action {

CameraWakeboard::CameraWakeboard(const InitArg& arg) : CameraAction(arg) {}

CameraWakeboard::~CameraWakeboard() = default;

bool CameraWakeboard::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraWakeboard::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraWakeboard::leave_() {
    CameraAction::leave_();
}

void CameraWakeboard::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraWakeboard::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
