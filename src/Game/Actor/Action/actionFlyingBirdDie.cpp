#include "Game/Actor/Action/actionFlyingBirdDie.h"

namespace uking::action {

FlyingBirdDie::FlyingBirdDie(const InitArg& arg) : FlyingActorDamageBase(arg) {}

FlyingBirdDie::~FlyingBirdDie() = default;

bool FlyingBirdDie::init_(sead::Heap* heap) {
    return FlyingActorDamageBase::init_(heap);
}

void FlyingBirdDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingActorDamageBase::enter_(params);
}

void FlyingBirdDie::leave_() {
    FlyingActorDamageBase::leave_();
}

void FlyingBirdDie::loadParams_() {
    FlyingActorDamageBase::loadParams_();
    getStaticParam(&mEnableHitGroundCheckTimer_s, "EnableHitGroundCheckTimer");
    getStaticParam(&mIsChangeStateFallOnce_s, "IsChangeStateFallOnce");
}

void FlyingBirdDie::calc_() {
    FlyingActorDamageBase::calc_();
}

}  // namespace uking::action
