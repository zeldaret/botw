#include "Game/AI/Action/actionForkDynASPlay.h"

namespace uking::action {

ForkDynASPlay::ForkDynASPlay(const InitArg& arg) : ForkASPlayBase(arg) {}

ForkDynASPlay::~ForkDynASPlay() = default;

bool ForkDynASPlay::init_(sead::Heap* heap) {
    return ForkASPlayBase::init_(heap);
}

void ForkDynASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASPlayBase::enter_(params);
}

void ForkDynASPlay::leave_() {
    ForkASPlayBase::leave_();
}

void ForkDynASPlay::loadParams_() {
    ForkASPlayBase::loadParams_();
    getDynamicParam(&mDynASKey_d, "DynASKey");
}

void ForkDynASPlay::calc_() {
    ForkASPlayBase::calc_();
}

}  // namespace uking::action
