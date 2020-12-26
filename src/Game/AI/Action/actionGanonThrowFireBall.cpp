#include "Game/AI/Action/actionGanonThrowFireBall.h"

namespace uking::action {

GanonThrowFireBall::GanonThrowFireBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonThrowFireBall::~GanonThrowFireBall() = default;

bool GanonThrowFireBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonThrowFireBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonThrowFireBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonThrowFireBall::loadParams_() {
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mFireBallScale_s, "FireBallScale");
    getStaticParam(&mBallAppearOffset_s, "BallAppearOffset");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mThrowPartsName_d, "ThrowPartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void GanonThrowFireBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
