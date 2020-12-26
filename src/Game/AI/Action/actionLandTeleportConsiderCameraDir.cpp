#include "Game/AI/Action/actionLandTeleportConsiderCameraDir.h"

namespace uking::action {

LandTeleportConsiderCameraDir::LandTeleportConsiderCameraDir(const InitArg& arg)
    : LandTeleport(arg) {}

LandTeleportConsiderCameraDir::~LandTeleportConsiderCameraDir() = default;

bool LandTeleportConsiderCameraDir::init_(sead::Heap* heap) {
    return LandTeleport::init_(heap);
}

void LandTeleportConsiderCameraDir::enter_(ksys::act::ai::InlineParamPack* params) {
    LandTeleport::enter_(params);
}

void LandTeleportConsiderCameraDir::leave_() {
    LandTeleport::leave_();
}

void LandTeleportConsiderCameraDir::loadParams_() {
    LandTeleport::loadParams_();
    getStaticParam(&mCameraDirCoeff_s, "CameraDirCoeff");
}

void LandTeleportConsiderCameraDir::calc_() {
    LandTeleport::calc_();
}

}  // namespace uking::action
