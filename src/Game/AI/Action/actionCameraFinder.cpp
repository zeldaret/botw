#include "Game/AI/Action/actionCameraFinder.h"

namespace uking::action {

CameraFinder::CameraFinder(const InitArg& arg) : CameraAction(arg) {}

CameraFinder::~CameraFinder() = default;

bool CameraFinder::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraFinder::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraFinder::leave_() {
    CameraAction::leave_();
}

void CameraFinder::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraFinder::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
