#include "Game/AI/AI/aiGanonFarAttackRootOnWall.h"

namespace uking::ai {

GanonFarAttackRootOnWall::GanonFarAttackRootOnWall(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonFarAttackRootOnWall::~GanonFarAttackRootOnWall() = default;

bool GanonFarAttackRootOnWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonFarAttackRootOnWall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonFarAttackRootOnWall::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonFarAttackRootOnWall::loadParams_() {
    getStaticParam(&mPillarMax_s, "PillarMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mViewPos_d, "ViewPos");
}

}  // namespace uking::ai
