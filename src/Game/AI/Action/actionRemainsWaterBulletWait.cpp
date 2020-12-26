#include "Game/AI/Action/actionRemainsWaterBulletWait.h"

namespace uking::action {

RemainsWaterBulletWait::RemainsWaterBulletWait(const InitArg& arg)
    : RemainsWaterBulletAction(arg) {}

RemainsWaterBulletWait::~RemainsWaterBulletWait() = default;

bool RemainsWaterBulletWait::init_(sead::Heap* heap) {
    return RemainsWaterBulletAction::init_(heap);
}

void RemainsWaterBulletWait::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsWaterBulletAction::enter_(params);
}

void RemainsWaterBulletWait::leave_() {
    RemainsWaterBulletAction::leave_();
}

void RemainsWaterBulletWait::loadParams_() {
    RemainsWaterBulletAction::loadParams_();
    getStaticParam(&mMaxChaseAngle_s, "MaxChaseAngle");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mChaseRate_s, "ChaseRate");
    getMapUnitParam(&mRemainsWaterBulletAngle_m, "RemainsWaterBulletAngle");
    getMapUnitParam(&mRemainsWaterBulletOffset_m, "RemainsWaterBulletOffset");
}

void RemainsWaterBulletWait::calc_() {
    RemainsWaterBulletAction::calc_();
}

}  // namespace uking::action
