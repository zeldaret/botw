#include "Game/AI/Action/actionForkHopInAir.h"

namespace uking::action {

ForkHopInAir::ForkHopInAir(const InitArg& arg) : Fork(arg) {}

ForkHopInAir::~ForkHopInAir() = default;

bool ForkHopInAir::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkHopInAir::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkHopInAir::leave_() {
    Fork::leave_();
}

void ForkHopInAir::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mHopHeight_s, "HopHeight");
}

void ForkHopInAir::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
