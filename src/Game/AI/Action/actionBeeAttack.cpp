#include "Game/AI/Action/actionBeeAttack.h"

namespace uking::action {

BeeAttack::BeeAttack(const InitArg& arg) : FlyMoveBase(arg) {}

BeeAttack::~BeeAttack() = default;

bool BeeAttack::init_(sead::Heap* heap) {
    return FlyMoveBase::init_(heap);
}

void BeeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyMoveBase::enter_(params);
}

void BeeAttack::leave_() {
    FlyMoveBase::leave_();
}

void BeeAttack::loadParams_() {
    FlyMoveBase::loadParams_();
    getStaticParam(&mThroughDist_s, "ThroughDist");
}

void BeeAttack::calc_() {
    FlyMoveBase::calc_();
}

}  // namespace uking::action
