#include "Game/AI/Action/actionForkAnimReset.h"

namespace uking::action {

ForkAnimReset::ForkAnimReset(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAnimReset::~ForkAnimReset() = default;

bool ForkAnimReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAnimReset::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAnimReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAnimReset::loadParams_() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkAnimReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
