#include "Game/AI/Action/actionForkAnimDriveTurn.h"

namespace uking::action {

ForkAnimDriveTurn::ForkAnimDriveTurn(const InitArg& arg) : ForkAnimDriveMove(arg) {}

ForkAnimDriveTurn::~ForkAnimDriveTurn() = default;

bool ForkAnimDriveTurn::init_(sead::Heap* heap) {
    return ForkAnimDriveMove::init_(heap);
}

void ForkAnimDriveTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAnimDriveMove::enter_(params);
}

void ForkAnimDriveTurn::leave_() {
    ForkAnimDriveMove::leave_();
}

void ForkAnimDriveTurn::loadParams_() {
    ForkAnimDriveMove::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkAnimDriveTurn::calc_() {
    ForkAnimDriveMove::calc_();
}

}  // namespace uking::action
