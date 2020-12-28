#include "Game/AI/Action/actionCameraEventFocusDistSetting.h"

namespace uking::action {

CameraEventFocusDistSetting::CameraEventFocusDistSetting(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CameraEventFocusDistSetting::~CameraEventFocusDistSetting() = default;

void CameraEventFocusDistSetting::loadParams_() {
    getDynamicParam2(&mClipIndex_d, "ClipIndex");
    getDynamicParam2(&mFocusDistStart_d, "FocusDistStart");
    getDynamicParam2(&mFocusDistEnd_d, "FocusDistEnd");
}

void CameraEventFocusDistSetting::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
