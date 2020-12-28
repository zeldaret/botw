#include "Game/AI/Action/actionFlyingCharacterDamage.h"

namespace uking::action {

FlyingCharacterDamage::FlyingCharacterDamage(const InitArg& arg) : FlyingCharacterDamageBase(arg) {}

bool FlyingCharacterDamage::init_(sead::Heap* heap) {
    return FlyingCharacterDamageBase::init_(heap);
}

void FlyingCharacterDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterDamageBase::enter_(params);
}

void FlyingCharacterDamage::leave_() {
    FlyingCharacterDamageBase::leave_();
}

void FlyingCharacterDamage::loadParams_() {
    FlyingCharacterDamageBase::loadParams_();
}

void FlyingCharacterDamage::calc_() {
    FlyingCharacterDamageBase::calc_();
}

}  // namespace uking::action
