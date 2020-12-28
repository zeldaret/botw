#include "Game/AI/Action/actionCameraRumble.h"

namespace uking::action {

CameraRumble::CameraRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void CameraRumble::loadParams_() {
    getDynamicParam2(&mPattern_d, "Pattern");
    getDynamicParam2(&mCount_d, "Count");
    getDynamicParam2(&mPower_d, "Power");
    getDynamicParam2(&mSideways_d, "Sideways");
}

}  // namespace uking::action
