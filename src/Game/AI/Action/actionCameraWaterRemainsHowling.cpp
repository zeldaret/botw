#include "Game/AI/Action/actionCameraWaterRemainsHowling.h"

namespace uking::action {

CameraWaterRemainsHowling::CameraWaterRemainsHowling(const InitArg& arg) : CameraAction(arg) {}

CameraWaterRemainsHowling::~CameraWaterRemainsHowling() = default;

bool CameraWaterRemainsHowling::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraWaterRemainsHowling::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraWaterRemainsHowling::leave_() {
    CameraAction::leave_();
}

void CameraWaterRemainsHowling::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraWaterRemainsHowling::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
