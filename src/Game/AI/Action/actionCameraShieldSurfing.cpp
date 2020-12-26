#include "Game/AI/Action/actionCameraShieldSurfing.h"

namespace uking::action {

CameraShieldSurfing::CameraShieldSurfing(const InitArg& arg) : CameraAction(arg) {}

CameraShieldSurfing::~CameraShieldSurfing() = default;

bool CameraShieldSurfing::init_(sead::Heap* heap) {
    return CameraAction::init_(heap);
}

void CameraShieldSurfing::enter_(ksys::act::ai::InlineParamPack* params) {
    CameraAction::enter_(params);
}

void CameraShieldSurfing::leave_() {
    CameraAction::leave_();
}

void CameraShieldSurfing::loadParams_() {
    getStaticParam(&mBowFlag_s, "BowFlag");
}

void CameraShieldSurfing::calc_() {
    CameraAction::calc_();
}

}  // namespace uking::action
