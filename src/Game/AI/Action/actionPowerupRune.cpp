#include "Game/AI/Action/actionPowerupRune.h"

namespace uking::action {

PowerupRune::PowerupRune(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PowerupRune::~PowerupRune() = default;

bool PowerupRune::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PowerupRune::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PowerupRune::leave_() {
    ksys::act::ai::Action::leave_();
}

void PowerupRune::loadParams_() {
    getDynamicParam(&mRuneType_d, "RuneType");
}

void PowerupRune::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
