#include "Game/AI/Action/actionAnimalStop.h"

namespace uking::action {

AnimalStop::AnimalStop(const InitArg& arg) : HorseWaitAction(arg) {}

AnimalStop::~AnimalStop() = default;

bool AnimalStop::init_(sead::Heap* heap) {
    return HorseWaitAction::init_(heap);
}

void AnimalStop::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseWaitAction::enter_(params);
}

void AnimalStop::leave_() {
    HorseWaitAction::leave_();
}

void AnimalStop::loadParams_() {
    HorseWaitAction::loadParams_();
    getStaticParam(&mIsFixAxisY_s, "IsFixAxisY");
}

void AnimalStop::calc_() {
    HorseWaitAction::calc_();
}

}  // namespace uking::action
