#include "Game/AI/Action/actionForkForceGetUp.h"

namespace uking::action {

ForkForceGetUp::ForkForceGetUp(const InitArg& arg) : ForkAlwaysForceGetUp(arg) {}

ForkForceGetUp::~ForkForceGetUp() = default;

bool ForkForceGetUp::init_(sead::Heap* heap) {
    return ForkAlwaysForceGetUp::init_(heap);
}

void ForkForceGetUp::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysForceGetUp::enter_(params);
}

void ForkForceGetUp::leave_() {
    ForkAlwaysForceGetUp::leave_();
}

void ForkForceGetUp::loadParams_() {
    ForkAlwaysForceGetUp::loadParams_();
}

void ForkForceGetUp::calc_() {
    ForkAlwaysForceGetUp::calc_();
}

}  // namespace uking::action
