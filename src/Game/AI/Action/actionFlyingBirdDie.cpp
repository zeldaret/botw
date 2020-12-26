#include "Game/AI/Action/actionFlyingBirdDie.h"

namespace uking::action {

FlyingBirdDie::FlyingBirdDie(const InitArg& arg) : FlyingCharacterDamageBase(arg) {}

FlyingBirdDie::~FlyingBirdDie() = default;

bool FlyingBirdDie::init_(sead::Heap* heap) {
    return FlyingCharacterDamageBase::init_(heap);
}

void FlyingBirdDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterDamageBase::enter_(params);
}

void FlyingBirdDie::leave_() {
    FlyingCharacterDamageBase::leave_();
}

void FlyingBirdDie::loadParams_() {
    FlyingCharacterDamageBase::loadParams_();
    getStaticParam(&mEnableHitGroundCheckTimer_s, "EnableHitGroundCheckTimer");
    getStaticParam(&mIsChangeStateFallOnce_s, "IsChangeStateFallOnce");
}

void FlyingBirdDie::calc_() {
    FlyingCharacterDamageBase::calc_();
}

}  // namespace uking::action
