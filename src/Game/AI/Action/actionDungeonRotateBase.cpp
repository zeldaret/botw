#include "Game/AI/Action/actionDungeonRotateBase.h"

namespace uking::action {

DungeonRotateBase::DungeonRotateBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonRotateBase::~DungeonRotateBase() = default;

bool DungeonRotateBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DungeonRotateBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonRotateBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void DungeonRotateBase::loadParams_() {
    getStaticParam(&mRotateAxisIndex_s, "RotateAxisIndex");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mRemainsPartType_m, "RemainsPartType");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
    getMapUnitParam(&mVelocityControlRate_m, "VelocityControlRate");
    getMapUnitParam(&mAngleVelocityControlAccelDeg_m, "AngleVelocityControlAccelDeg");
}

void DungeonRotateBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
