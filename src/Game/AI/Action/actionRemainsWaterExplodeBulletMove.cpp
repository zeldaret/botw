#include "Game/AI/Action/actionRemainsWaterExplodeBulletMove.h"

namespace uking::action {

RemainsWaterExplodeBulletMove::RemainsWaterExplodeBulletMove(const InitArg& arg)
    : RemainsWaterBulletAction(arg) {}

RemainsWaterExplodeBulletMove::~RemainsWaterExplodeBulletMove() = default;

bool RemainsWaterExplodeBulletMove::init_(sead::Heap* heap) {
    return RemainsWaterBulletAction::init_(heap);
}

void RemainsWaterExplodeBulletMove::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsWaterBulletAction::enter_(params);
}

void RemainsWaterExplodeBulletMove::leave_() {
    RemainsWaterBulletAction::leave_();
}

void RemainsWaterExplodeBulletMove::loadParams_() {
    RemainsWaterBulletAction::loadParams_();
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mCloseRadius_s, "CloseRadius");
    getStaticParam(&mChaseAngleMulRate_s, "ChaseAngleMulRate");
    getStaticParam(&mFarRadius_s, "FarRadius");
    getStaticParam(&mChaseRotSpdRate_s, "ChaseRotSpdRate");
    getStaticParam(&mChaseSpdRate_s, "ChaseSpdRate");
    getMapUnitParam(&mRemainsWaterBulletAngle_m, "RemainsWaterBulletAngle");
    getMapUnitParam(&mRemainsWaterBulletOffset_m, "RemainsWaterBulletOffset");
}

void RemainsWaterExplodeBulletMove::calc_() {
    RemainsWaterBulletAction::calc_();
}

}  // namespace uking::action
