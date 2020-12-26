#include "Game/AI/Action/actionForkASPlay.h"

namespace uking::action {

ForkASPlay::ForkASPlay(const InitArg& arg) : ForkASPlayBase(arg) {}

ForkASPlay::~ForkASPlay() = default;

bool ForkASPlay::init_(sead::Heap* heap) {
    return ForkASPlayBase::init_(heap);
}

void ForkASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASPlayBase::enter_(params);
}

void ForkASPlay::leave_() {
    ForkASPlayBase::leave_();
}

void ForkASPlay::loadParams_() {
    ForkASPlayBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ForkASPlay::calc_() {
    ForkASPlayBase::calc_();
}

}  // namespace uking::action
