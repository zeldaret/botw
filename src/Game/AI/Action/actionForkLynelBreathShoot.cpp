#include "Game/AI/Action/actionForkLynelBreathShoot.h"

namespace uking::action {

ForkLynelBreathShoot::ForkLynelBreathShoot(const InitArg& arg) : ForkVacuumShootToTarget(arg) {}

ForkLynelBreathShoot::~ForkLynelBreathShoot() = default;

bool ForkLynelBreathShoot::init_(sead::Heap* heap) {
    return ForkVacuumShootToTarget::init_(heap);
}

void ForkLynelBreathShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkVacuumShootToTarget::enter_(params);
}

void ForkLynelBreathShoot::leave_() {
    ForkVacuumShootToTarget::leave_();
}

void ForkLynelBreathShoot::loadParams_() {
    ForkVacuumShootToTarget::loadParams_();
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mRange_s, "Range");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mShootDir_s, "ShootDir");
}

void ForkLynelBreathShoot::calc_() {
    ForkVacuumShootToTarget::calc_();
}

}  // namespace uking::action
