#include "Game/AI/Action/actionDungeonMoveAlwaysVibrateCam.h"

namespace uking::action {

DungeonMoveAlwaysVibrateCam::DungeonMoveAlwaysVibrateCam(const InitArg& arg) : DungeonMove(arg) {}

DungeonMoveAlwaysVibrateCam::~DungeonMoveAlwaysVibrateCam() = default;

bool DungeonMoveAlwaysVibrateCam::init_(sead::Heap* heap) {
    return DungeonMove::init_(heap);
}

void DungeonMoveAlwaysVibrateCam::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonMove::enter_(params);
}

void DungeonMoveAlwaysVibrateCam::leave_() {
    DungeonMove::leave_();
}

void DungeonMoveAlwaysVibrateCam::loadParams_() {
    DungeonMove::loadParams_();
    getStaticParam(&mIsSilentOnSuccess_s, "IsSilentOnSuccess");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

void DungeonMoveAlwaysVibrateCam::calc_() {
    DungeonMove::calc_();
}

}  // namespace uking::action
