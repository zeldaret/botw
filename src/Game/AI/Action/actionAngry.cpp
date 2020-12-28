#include "Game/AI/Action/actionAngry.h"

namespace uking::action {

Angry::Angry(const InitArg& arg) : ActionWithAS(arg) {}

bool Angry::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void Angry::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void Angry::leave_() {
    ActionWithAS::leave_();
}

void Angry::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void Angry::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
