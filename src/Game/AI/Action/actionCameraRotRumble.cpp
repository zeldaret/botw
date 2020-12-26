#include "Game/AI/Action/actionCameraRotRumble.h"

namespace uking::action {

CameraRotRumble::CameraRotRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraRotRumble::~CameraRotRumble() = default;

bool CameraRotRumble::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraRotRumble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraRotRumble::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraRotRumble::loadParams_() {
    getDynamicParam2(&mPattern_d, "Pattern");
    getDynamicParam2(&mCount_d, "Count");
    getDynamicParam2(&mPower_d, "Power");
}

void CameraRotRumble::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
