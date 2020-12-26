#include "Game/AI/Action/actionCameraMotorcycle.h"

namespace uking::action {

CameraMotorcycle::CameraMotorcycle(const InitArg& arg) : CameraAction(arg) {}

CameraMotorcycle::~CameraMotorcycle() = default;

bool CameraMotorcycle::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraMotorcycle::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraMotorcycle::leave_() {
    CameraAction::leave_();
}

void CameraMotorcycle::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraMotorcycle::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
