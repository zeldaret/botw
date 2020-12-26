#include "Game/AI/Action/actionForkGanonBeastWeakPointOff.h"

namespace uking::action {

ForkGanonBeastWeakPointOff::ForkGanonBeastWeakPointOff(const InitArg& arg)
    : ForkGanonBeastWeakPoint(arg) {}

ForkGanonBeastWeakPointOff::~ForkGanonBeastWeakPointOff() = default;

bool ForkGanonBeastWeakPointOff::init_(sead::Heap* heap) {
    return ForkGanonBeastWeakPoint::init_(heap);
}

void ForkGanonBeastWeakPointOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkGanonBeastWeakPoint::enter_(params);
}

void ForkGanonBeastWeakPointOff::leave_() {
    ForkGanonBeastWeakPoint::leave_();
}

void ForkGanonBeastWeakPointOff::loadParams_() {
    ForkGanonBeastWeakPoint::loadParams_();
}

void ForkGanonBeastWeakPointOff::calc_() {
    ForkGanonBeastWeakPoint::calc_();
}

}  // namespace uking::action
