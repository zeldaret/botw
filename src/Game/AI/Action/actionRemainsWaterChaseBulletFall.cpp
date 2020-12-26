#include "Game/AI/Action/actionRemainsWaterChaseBulletFall.h"

namespace uking::action {

RemainsWaterChaseBulletFall::RemainsWaterChaseBulletFall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsWaterChaseBulletFall::~RemainsWaterChaseBulletFall() = default;

bool RemainsWaterChaseBulletFall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsWaterChaseBulletFall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsWaterChaseBulletFall::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsWaterChaseBulletFall::loadParams_() {
    getStaticParam(&mEndTimer_s, "EndTimer");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mSetVelocity_s, "SetVelocity");
    getStaticParam(&mSetVelocityFromWeapon_s, "SetVelocityFromWeapon");
}

void RemainsWaterChaseBulletFall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
