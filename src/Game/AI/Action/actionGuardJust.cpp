#include "Game/AI/Action/actionGuardJust.h"

namespace uking::action {

GuardJust::GuardJust(const InitArg& arg) : OnetimeStopASPlay(arg) {}

GuardJust::~GuardJust() = default;

bool GuardJust::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void GuardJust::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void GuardJust::leave_() {
    OnetimeStopASPlay::leave_();
}

void GuardJust::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void GuardJust::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
