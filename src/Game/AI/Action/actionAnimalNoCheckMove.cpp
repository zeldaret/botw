#include "Game/AI/Action/actionAnimalNoCheckMove.h"

namespace uking::action {

AnimalNoCheckMove::AnimalNoCheckMove(const InitArg& arg) : AnimalMove(arg) {}

AnimalNoCheckMove::~AnimalNoCheckMove() = default;

bool AnimalNoCheckMove::init_(sead::Heap* heap) {
    return AnimalMove::init_(heap);
}

void AnimalNoCheckMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMove::enter_(params);
}

void AnimalNoCheckMove::leave_() {
    AnimalMove::leave_();
}

void AnimalNoCheckMove::loadParams_() {
    AnimalMove::loadParams_();
}

void AnimalNoCheckMove::calc_() {
    AnimalMove::calc_();
}

}  // namespace uking::action
