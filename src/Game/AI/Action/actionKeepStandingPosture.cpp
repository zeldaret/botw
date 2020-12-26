#include "Game/AI/Action/actionKeepStandingPosture.h"

namespace uking::action {

KeepStandingPosture::KeepStandingPosture(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KeepStandingPosture::~KeepStandingPosture() = default;

bool KeepStandingPosture::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KeepStandingPosture::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KeepStandingPosture::leave_() {
    ksys::act::ai::Action::leave_();
}

void KeepStandingPosture::loadParams_() {}

void KeepStandingPosture::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
