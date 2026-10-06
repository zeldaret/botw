#include "Game/Actor/AI/aiDungeonRotateTagApp.h"

namespace uking::ai {

DungeonRotateTagApp::DungeonRotateTagApp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTagApp::~DungeonRotateTagApp() = default;

bool DungeonRotateTagApp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTagApp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonRotateTagApp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTagApp::loadParams_() {
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
}

}  // namespace uking::ai
