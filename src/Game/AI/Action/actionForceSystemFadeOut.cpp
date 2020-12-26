#include "Game/AI/Action/actionForceSystemFadeOut.h"

namespace uking::action {

ForceSystemFadeOut::ForceSystemFadeOut(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceSystemFadeOut::~ForceSystemFadeOut() = default;

bool ForceSystemFadeOut::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceSystemFadeOut::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceSystemFadeOut::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceSystemFadeOut::loadParams_() {}

void ForceSystemFadeOut::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
