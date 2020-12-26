#include "Game/AI/Action/actionCameraHorseLockOnEmpty.h"

namespace uking::action {

CameraHorseLockOnEmpty::CameraHorseLockOnEmpty(const InitArg& arg) : CameraAction(arg) {}

CameraHorseLockOnEmpty::~CameraHorseLockOnEmpty() = default;

bool CameraHorseLockOnEmpty::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraHorseLockOnEmpty::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraHorseLockOnEmpty::leave_() {
    CameraAction::leave_();
}

void CameraHorseLockOnEmpty::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraHorseLockOnEmpty::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
