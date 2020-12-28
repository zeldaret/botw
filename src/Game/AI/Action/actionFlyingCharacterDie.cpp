#include "Game/AI/Action/actionFlyingCharacterDie.h"

namespace uking::action {

FlyingCharacterDie::FlyingCharacterDie(const InitArg& arg) : FlyingCharacterDamageBase(arg) {}

bool FlyingCharacterDie::init_(sead::Heap* heap) {
    return FlyingCharacterDamageBase::init_(heap);
}

void FlyingCharacterDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterDamageBase::enter_(params);
}

void FlyingCharacterDie::leave_() {
    FlyingCharacterDamageBase::leave_();
}

void FlyingCharacterDie::loadParams_() {
    FlyingCharacterDamageBase::loadParams_();
}

void FlyingCharacterDie::calc_() {
    FlyingCharacterDamageBase::calc_();
}

}  // namespace uking::action
