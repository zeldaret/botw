#include "Game/Actor/Action/actionArrowChargeAndShoot.h"

namespace uking::action {

ArrowChargeAndShoot::ArrowChargeAndShoot(const InitArg& arg) : ShootArrow(arg) {}

ArrowChargeAndShoot::~ArrowChargeAndShoot() = default;

bool ArrowChargeAndShoot::init_(sead::Heap* heap) {
    return ShootArrow::init_(heap);
}

void ArrowChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootArrow::enter_(params);
}

void ArrowChargeAndShoot::leave_() {
    ShootArrow::leave_();
}

void ArrowChargeAndShoot::loadParams_() {
    ShootArrow::loadParams_();
}

void ArrowChargeAndShoot::calc_() {
    ShootArrow::calc_();
}

}  // namespace uking::action
