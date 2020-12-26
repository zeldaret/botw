#include "Game/AI/Action/actionForceEndPlayerSlow.h"

namespace uking::action {

ForceEndPlayerSlow::ForceEndPlayerSlow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceEndPlayerSlow::~ForceEndPlayerSlow() = default;

bool ForceEndPlayerSlow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceEndPlayerSlow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceEndPlayerSlow::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceEndPlayerSlow::loadParams_() {}

void ForceEndPlayerSlow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
