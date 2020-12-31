#include "Game/AI/AI/aiDungeonRotateTag3D.h"

namespace uking::ai {

DungeonRotateTag3D::DungeonRotateTag3D(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTag3D::~DungeonRotateTag3D() = default;

bool DungeonRotateTag3D::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTag3D::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonRotateTag3D::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTag3D::loadParams_() {
    getStaticParam(&mTargetRad_s, "TargetRad");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mRemainsPartType_m, "RemainsPartType");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

}  // namespace uking::ai
