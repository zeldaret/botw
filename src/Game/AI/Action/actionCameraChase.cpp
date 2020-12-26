#include "Game/AI/Action/actionCameraChase.h"

namespace uking::action {

CameraChase::CameraChase(const InitArg& arg) : CameraAction(arg) {}

CameraChase::~CameraChase() = default;

bool CameraChase::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraChase::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraChase::leave_() {
    CameraAction::leave_();
}

void CameraChase::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraChase::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
