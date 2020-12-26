#include "Game/AI/Action/actionCameraVibrate.h"

namespace uking::action {

CameraVibrate::CameraVibrate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CameraVibrate::~CameraVibrate() = default;

bool CameraVibrate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CameraVibrate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CameraVibrate::leave_() {
    ksys::act::ai::Action::leave_();
}

void CameraVibrate::loadParams_() {
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
    getStaticParam(&mIsSound_s, "IsSound");
    getStaticParam(&mStartSoundName_s, "StartSoundName");
    getStaticParam(&mLoopSoundName_s, "LoopSoundName");
}

void CameraVibrate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
