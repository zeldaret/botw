#include "Game/AI/Action/actionApplyMoveImpulse.h"

namespace uking::action {

ApplyMoveImpulse::ApplyMoveImpulse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ApplyMoveImpulse::~ApplyMoveImpulse() = default;

bool ApplyMoveImpulse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ApplyMoveImpulse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ApplyMoveImpulse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ApplyMoveImpulse::loadParams_() {
    getStaticParam(&mFellImpRate_s, "FellImpRate");
    getStaticParam(&mFellRotRate_s, "FellRotRate");
}

void ApplyMoveImpulse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
