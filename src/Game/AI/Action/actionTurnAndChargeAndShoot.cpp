#include "Game/AI/Action/actionTurnAndChargeAndShoot.h"

namespace uking::action {

TurnAndChargeAndShoot::TurnAndChargeAndShoot(const InitArg& arg) : ChargeAndShoot(arg) {}

TurnAndChargeAndShoot::~TurnAndChargeAndShoot() = default;

bool TurnAndChargeAndShoot::init_(sead::Heap* heap) {
    return ChargeAndShoot::init_(heap);
}

void TurnAndChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ChargeAndShoot::enter_(params);
}

void TurnAndChargeAndShoot::leave_() {
    ChargeAndShoot::leave_();
}

void TurnAndChargeAndShoot::loadParams_() {
    ChargeAndShoot::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void TurnAndChargeAndShoot::calc_() {
    ChargeAndShoot::calc_();
}

}  // namespace uking::action
