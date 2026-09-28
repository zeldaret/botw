#include "Game/Actor/Action/actionFlyingCharacterDamage.h"

namespace uking::action {

FlyingCharacterDamage::FlyingCharacterDamage(const InitArg& arg) : FlyingActorDamageBase(arg) {}

bool FlyingCharacterDamage::init_(sead::Heap* heap) {
    return FlyingActorDamageBase::init_(heap);
}

void FlyingCharacterDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingActorDamageBase::enter_(params);
}

void FlyingCharacterDamage::leave_() {
    FlyingActorDamageBase::leave_();
}

void FlyingCharacterDamage::loadParams_() {
    FlyingActorDamageBase::loadParams_();
}

void FlyingCharacterDamage::calc_() {
    FlyingActorDamageBase::calc_();
}

}  // namespace uking::action
