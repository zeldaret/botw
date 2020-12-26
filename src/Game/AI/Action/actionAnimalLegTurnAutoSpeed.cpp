#include "Game/AI/Action/actionAnimalLegTurnAutoSpeed.h"

namespace uking::action {

AnimalLegTurnAutoSpeed::AnimalLegTurnAutoSpeed(const InitArg& arg) : ForkAnimalASPlay(arg) {}

AnimalLegTurnAutoSpeed::~AnimalLegTurnAutoSpeed() = default;

bool AnimalLegTurnAutoSpeed::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void AnimalLegTurnAutoSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAnimalASPlay::enter_(params);
}

void AnimalLegTurnAutoSpeed::leave_() {
    ForkAnimalASPlay::leave_();
}

void AnimalLegTurnAutoSpeed::loadParams_() {
    ForkAnimalASPlay::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalLegTurnAutoSpeed::calc_() {
    ForkAnimalASPlay::calc_();
}

}  // namespace uking::action
