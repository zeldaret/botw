#include "Game/AI/Action/actionEatAndHeal.h"

namespace uking::action {

EatAndHeal::EatAndHeal(const InitArg& arg) : AnimalEatAction(arg) {}

EatAndHeal::~EatAndHeal() = default;

bool EatAndHeal::init_(sead::Heap* heap) {
    return AnimalEatAction::init_(heap);
}

void EatAndHeal::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalEatAction::enter_(params);
}

void EatAndHeal::leave_() {
    AnimalEatAction::leave_();
}

void EatAndHeal::loadParams_() {
    AnimalEatAction::loadParams_();
}

void EatAndHeal::calc_() {
    AnimalEatAction::calc_();
}

}  // namespace uking::action
