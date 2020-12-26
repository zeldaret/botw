#include "Game/AI/Action/actionIgniteGrabAndShoot.h"

namespace uking::action {

IgniteGrabAndShoot::IgniteGrabAndShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IgniteGrabAndShoot::~IgniteGrabAndShoot() = default;

bool IgniteGrabAndShoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IgniteGrabAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IgniteGrabAndShoot::leave_() {
    ksys::act::ai::Action::leave_();
}

void IgniteGrabAndShoot::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
}

void IgniteGrabAndShoot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
