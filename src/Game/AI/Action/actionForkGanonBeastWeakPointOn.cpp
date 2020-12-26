#include "Game/AI/Action/actionForkGanonBeastWeakPointOn.h"

namespace uking::action {

ForkGanonBeastWeakPointOn::ForkGanonBeastWeakPointOn(const InitArg& arg)
    : ForkGanonBeastWeakPoint(arg) {}

ForkGanonBeastWeakPointOn::~ForkGanonBeastWeakPointOn() = default;

bool ForkGanonBeastWeakPointOn::init_(sead::Heap* heap) {
    return ForkGanonBeastWeakPoint::init_(heap);
}

void ForkGanonBeastWeakPointOn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkGanonBeastWeakPoint::enter_(params);
}

void ForkGanonBeastWeakPointOn::leave_() {
    ForkGanonBeastWeakPoint::leave_();
}

void ForkGanonBeastWeakPointOn::loadParams_() {
    ForkGanonBeastWeakPoint::loadParams_();
}

void ForkGanonBeastWeakPointOn::calc_() {
    ForkGanonBeastWeakPoint::calc_();
}

}  // namespace uking::action
