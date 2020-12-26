#include "Game/AI/Action/actionForkAnimDriveMove.h"

namespace uking::action {

ForkAnimDriveMove::ForkAnimDriveMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAnimDriveMove::~ForkAnimDriveMove() = default;

bool ForkAnimDriveMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAnimDriveMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAnimDriveMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAnimDriveMove::loadParams_() {
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkAnimDriveMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
