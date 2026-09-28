#include "Game/Actor/Action/actionTurnAndChargeAndShoot.h"

namespace uking::action {

TurnAndChargeAndShoot::TurnAndChargeAndShoot(const InitArg& arg) : ArrowChargeAndShoot(arg) {}

TurnAndChargeAndShoot::~TurnAndChargeAndShoot() = default;

bool TurnAndChargeAndShoot::init_(sead::Heap* heap) {
    return ArrowChargeAndShoot::init_(heap);
}

void TurnAndChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowChargeAndShoot::enter_(params);
}

void TurnAndChargeAndShoot::leave_() {
    ArrowChargeAndShoot::leave_();
}

void TurnAndChargeAndShoot::loadParams_() {
    ArrowChargeAndShoot::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void TurnAndChargeAndShoot::calc_() {
    ArrowChargeAndShoot::calc_();
}

}  // namespace uking::action
