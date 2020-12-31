#include "Game/AI/AI/aiElectricBall.h"

namespace uking::ai {

ElectricBall::ElectricBall(const InitArg& arg) : SimpleLiftable(arg) {}

bool ElectricBall::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void ElectricBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void ElectricBall::leave_() {
    SimpleLiftable::leave_();
}

void ElectricBall::loadParams_() {
    getStaticParam(&mTargetVol_s, "TargetVol");
}

}  // namespace uking::ai
