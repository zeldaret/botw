#include "Game/AI/Action/actionShootingStartFlying.h"

namespace uking::action {

ShootingStartFlying::ShootingStartFlying(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShootingStartFlying::~ShootingStartFlying() = default;

bool ShootingStartFlying::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShootingStartFlying::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ShootingStartFlying::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShootingStartFlying::loadParams_() {
    getStaticParam(&mInitialVelocityMax_s, "InitialVelocityMax");
    getStaticParam(&mInitialVelocityMin_s, "InitialVelocityMin");
    getStaticParam(&mInitialAngleRange_s, "InitialAngleRange");
    getStaticParam(&mLookSuccessRate_s, "LookSuccessRate");
    getStaticParam(&mMaxWaterDepth_s, "MaxWaterDepth");
    getStaticParam(&mGravity_s, "Gravity");
}

void ShootingStartFlying::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
