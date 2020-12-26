#include "Game/AI/Action/actionForkAlwayForceGetUpVelocityDir.h"

namespace uking::action {

ForkAlwayForceGetUpVelocityDir::ForkAlwayForceGetUpVelocityDir(const InitArg& arg)
    : ForkAlwaysForceGetUp(arg) {}

ForkAlwayForceGetUpVelocityDir::~ForkAlwayForceGetUpVelocityDir() = default;

bool ForkAlwayForceGetUpVelocityDir::init_(sead::Heap* heap) {
    return ForkAlwaysForceGetUp::init_(heap);
}

void ForkAlwayForceGetUpVelocityDir::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysForceGetUp::enter_(params);
}

void ForkAlwayForceGetUpVelocityDir::leave_() {
    ForkAlwaysForceGetUp::leave_();
}

void ForkAlwayForceGetUpVelocityDir::loadParams_() {
    ForkAlwaysForceGetUp::loadParams_();
}

void ForkAlwayForceGetUpVelocityDir::calc_() {
    ForkAlwaysForceGetUp::calc_();
}

}  // namespace uking::action
