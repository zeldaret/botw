#include "Game/AI/AI/aiGanonBeamOnFloor.h"

namespace uking::ai {

GanonBeamOnFloor::GanonBeamOnFloor(const InitArg& arg) : LastBossShootNormalArrowRoot(arg) {}

GanonBeamOnFloor::~GanonBeamOnFloor() = default;

bool GanonBeamOnFloor::init_(sead::Heap* heap) {
    return LastBossShootNormalArrowRoot::init_(heap);
}

void GanonBeamOnFloor::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossShootNormalArrowRoot::enter_(params);
}

void GanonBeamOnFloor::leave_() {
    LastBossShootNormalArrowRoot::leave_();
}

void GanonBeamOnFloor::loadParams_() {
    LastBossShootNormalArrowRoot::loadParams_();
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
    getStaticParam(&mKeepMinDist_s, "KeepMinDist");
    getStaticParam(&mTurnRate_s, "TurnRate");
    getStaticParam(&mWalkAS_s, "WalkAS");
    getStaticParam(&mTurnAS_s, "TurnAS");
}

}  // namespace uking::ai
