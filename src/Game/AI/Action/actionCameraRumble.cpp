#include "Game/AI/Action/actionCameraRumble.h"

namespace uking::action {

CameraRumble::CameraRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraRumble::~CameraRumble() = default;

bool CameraRumble::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraRumble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraRumble::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraRumble::loadParams_() {
    getDynamicParam2(&mPattern_d, "Pattern");
    getDynamicParam2(&mCount_d, "Count");
    getDynamicParam2(&mPower_d, "Power");
    getDynamicParam2(&mSideways_d, "Sideways");
}

void CameraRumble::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
