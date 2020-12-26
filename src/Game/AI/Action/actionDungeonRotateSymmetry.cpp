#include "Game/AI/Action/actionDungeonRotateSymmetry.h"

namespace uking::action {

DungeonRotateSymmetry::DungeonRotateSymmetry(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonRotateSymmetry::~DungeonRotateSymmetry() = default;

bool DungeonRotateSymmetry::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DungeonRotateSymmetry::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonRotateSymmetry::leave_() {
    ksys::act::ai::Action::leave_();
}

void DungeonRotateSymmetry::loadParams_() {
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mRemainsPartType_m, "RemainsPartType");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

void DungeonRotateSymmetry::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
