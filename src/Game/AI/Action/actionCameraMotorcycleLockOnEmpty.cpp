#include "Game/AI/Action/actionCameraMotorcycleLockOnEmpty.h"

namespace uking::action {

CameraMotorcycleLockOnEmpty::CameraMotorcycleLockOnEmpty(const InitArg& arg) : CameraAction(arg) {}

CameraMotorcycleLockOnEmpty::~CameraMotorcycleLockOnEmpty() = default;

bool CameraMotorcycleLockOnEmpty::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraMotorcycleLockOnEmpty::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraMotorcycleLockOnEmpty::leave_() {
    CameraAction::leave_();
}

void CameraMotorcycleLockOnEmpty::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraMotorcycleLockOnEmpty::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
