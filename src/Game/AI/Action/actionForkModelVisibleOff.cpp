#include "Game/AI/Action/actionForkModelVisibleOff.h"

namespace uking::action {

ForkModelVisibleOff::ForkModelVisibleOff(const InitArg& arg) : Fork(arg) {}

ForkModelVisibleOff::~ForkModelVisibleOff() = default;

bool ForkModelVisibleOff::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkModelVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkModelVisibleOff::leave_() {
    Fork::leave_();
}

void ForkModelVisibleOff::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mUseFadeIn_s, "UseFadeIn");
    getStaticParam(&mUseASEvent_s, "UseASEvent");
}

void ForkModelVisibleOff::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
