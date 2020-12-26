#include "Game/AI/Action/actionCameraClimbObj.h"

namespace uking::action {

CameraClimbObj::CameraClimbObj(const InitArg& arg) : CameraAction(arg) {}

CameraClimbObj::~CameraClimbObj() = default;

bool CameraClimbObj::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraClimbObj::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraClimbObj::leave_() {
    CameraAction::leave_();
}

void CameraClimbObj::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraClimbObj::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
