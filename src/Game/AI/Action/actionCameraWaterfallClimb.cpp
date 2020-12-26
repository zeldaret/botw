#include "Game/AI/Action/actionCameraWaterfallClimb.h"

namespace uking::action {

CameraWaterfallClimb::CameraWaterfallClimb(const InitArg& arg) : CameraAction(arg) {}

CameraWaterfallClimb::~CameraWaterfallClimb() = default;

bool CameraWaterfallClimb::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraWaterfallClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraWaterfallClimb::leave_() {
    CameraAction::leave_();
}

void CameraWaterfallClimb::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraWaterfallClimb::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
