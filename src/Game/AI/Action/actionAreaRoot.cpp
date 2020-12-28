#include "Game/AI/Action/actionAreaRoot.h"

namespace uking::action {

AreaRoot::AreaRoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaRoot::~AreaRoot() = default;

bool AreaRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AreaRoot::loadParams_() {
    getStaticParam(&mAutoSaveInterval_s, "AutoSaveInterval");
    getMapUnitParam(&mCameraPriority_m, "CameraPriority");
    getMapUnitParam(&mAutoSave_m, "AutoSave");
    getMapUnitParam(&mForceCalcInEvent_m, "ForceCalcInEvent");
    getMapUnitParam(&mCameraSet_m, "CameraSet");
    getMapUnitParam(&mShape_m, "Shape");
    getMapUnitParam(&mWarpDestMapName_m, "WarpDestMapName");
    getMapUnitParam(&mWarpDestPosName_m, "WarpDestPosName");
}

void AreaRoot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
