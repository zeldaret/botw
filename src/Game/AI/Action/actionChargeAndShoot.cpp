#include "Game/AI/Action/actionChargeAndShoot.h"

namespace uking::action {

ChargeAndShoot::ChargeAndShoot(const InitArg& arg) : ShootArrow(arg) {}

ChargeAndShoot::~ChargeAndShoot() = default;

bool ChargeAndShoot::init_(sead::Heap* heap) {
    return ShootArrow::init_(heap);
}

void ChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootArrow::enter_(params);
}

void ChargeAndShoot::leave_() {
    ShootArrow::leave_();
}

void ChargeAndShoot::loadParams_() {
    ShootArrow::loadParams_();
}

void ChargeAndShoot::calc_() {
    ShootArrow::calc_();
}

}  // namespace uking::action
