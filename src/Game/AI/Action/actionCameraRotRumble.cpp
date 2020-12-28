#include "Game/AI/Action/actionCameraRotRumble.h"

namespace uking::action {

CameraRotRumble::CameraRotRumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void CameraRotRumble::loadParams_() {
    getDynamicParam2(&mPattern_d, "Pattern");
    getDynamicParam2(&mCount_d, "Count");
    getDynamicParam2(&mPower_d, "Power");
}

}  // namespace uking::action
