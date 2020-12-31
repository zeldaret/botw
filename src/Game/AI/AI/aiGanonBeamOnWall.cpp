#include "Game/AI/AI/aiGanonBeamOnWall.h"

namespace uking::ai {

GanonBeamOnWall::GanonBeamOnWall(const InitArg& arg) : LastBossShootNormalArrowRoot(arg) {}

GanonBeamOnWall::~GanonBeamOnWall() = default;

bool GanonBeamOnWall::init_(sead::Heap* heap) {
    return LastBossShootNormalArrowRoot::init_(heap);
}

void GanonBeamOnWall::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossShootNormalArrowRoot::enter_(params);
}

void GanonBeamOnWall::leave_() {
    LastBossShootNormalArrowRoot::leave_();
}

void GanonBeamOnWall::loadParams_() {
    LastBossShootNormalArrowRoot::loadParams_();
}

}  // namespace uking::ai
