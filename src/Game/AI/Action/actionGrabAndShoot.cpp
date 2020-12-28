#include "Game/AI/Action/actionGrabAndShoot.h"

namespace uking::action {

GrabAndShoot::GrabAndShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GrabAndShoot::~GrabAndShoot() = default;

void GrabAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GrabAndShoot::leave_() {
    ksys::act::ai::Action::leave_();
}

void GrabAndShoot::loadParams_() {
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mShootSpeed_s, "ShootSpeed");
    getStaticParam(&mShootAng_s, "ShootAng");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mBlurMax_s, "BlurMax");
}

void GrabAndShoot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
