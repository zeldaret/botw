#include "Game/AI/Action/actionForkAnimDriveFreeMoving.h"

namespace uking::action {

ForkAnimDriveFreeMoving::ForkAnimDriveFreeMoving(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAnimDriveFreeMoving::~ForkAnimDriveFreeMoving() = default;

bool ForkAnimDriveFreeMoving::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAnimDriveFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAnimDriveFreeMoving::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAnimDriveFreeMoving::loadParams_() {}

void ForkAnimDriveFreeMoving::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
