#include "Game/AI/Action/actionRemainsWaterBulletRevive.h"

namespace uking::action {

RemainsWaterBulletRevive::RemainsWaterBulletRevive(const InitArg& arg)
    : RemainsWaterBulletWait(arg) {}

RemainsWaterBulletRevive::~RemainsWaterBulletRevive() = default;

bool RemainsWaterBulletRevive::init_(sead::Heap* heap) {
    return RemainsWaterBulletWait::init_(heap);
}

void RemainsWaterBulletRevive::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsWaterBulletWait::enter_(params);
}

void RemainsWaterBulletRevive::leave_() {
    RemainsWaterBulletWait::leave_();
}

void RemainsWaterBulletRevive::loadParams_() {
    RemainsWaterBulletWait::loadParams_();
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void RemainsWaterBulletRevive::calc_() {
    RemainsWaterBulletWait::calc_();
}

}  // namespace uking::action
