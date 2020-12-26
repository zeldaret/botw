#include "Game/AI/Action/actionFreeMoveToNearGround.h"

namespace uking::action {

FreeMoveToNearGround::FreeMoveToNearGround(const InitArg& arg) : FreeMoveToTarget(arg) {}

FreeMoveToNearGround::~FreeMoveToNearGround() = default;

bool FreeMoveToNearGround::init_(sead::Heap* heap) {
    return FreeMoveToTarget::init_(heap);
}

void FreeMoveToNearGround::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMoveToTarget::enter_(params);
}

void FreeMoveToNearGround::leave_() {
    FreeMoveToTarget::leave_();
}

void FreeMoveToNearGround::loadParams_() {
    FreeMoveToTarget::loadParams_();
    getStaticParam(&mReduceSpeedRateWithWind_s, "ReduceSpeedRateWithWind");
    getStaticParam(&mWindVelocityLimit4Reduce_s, "WindVelocityLimit4Reduce");
}

void FreeMoveToNearGround::calc_() {
    FreeMoveToTarget::calc_();
}

}  // namespace uking::action
