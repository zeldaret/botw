#include "Game/AI/Action/actionForkRagdollOff.h"

namespace uking::action {

ForkRagdollOff::ForkRagdollOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkRagdollOff::~ForkRagdollOff() = default;

bool ForkRagdollOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkRagdollOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkRagdollOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkRagdollOff::loadParams_() {
    getStaticParam(&mOffTiming_s, "OffTiming");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForkRagdollOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
