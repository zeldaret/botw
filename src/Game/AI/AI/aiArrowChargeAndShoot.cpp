#include "Game/AI/AI/aiArrowChargeAndShoot.h"

namespace uking::ai {

ArrowChargeAndShoot::ArrowChargeAndShoot(const InitArg& arg) : SeqTwoAction(arg) {}

ArrowChargeAndShoot::~ArrowChargeAndShoot() = default;

bool ArrowChargeAndShoot::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void ArrowChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void ArrowChargeAndShoot::leave_() {
    SeqTwoAction::leave_();
}

void ArrowChargeAndShoot::loadParams_() {
    SeqTwoAction::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
