#include "Game/AI/Action/actionForkFreeMoving.h"

namespace uking::action {

ForkFreeMoving::ForkFreeMoving(const InitArg& arg) : FreeMovingAction(arg) {}

ForkFreeMoving::~ForkFreeMoving() = default;

bool ForkFreeMoving::init_(sead::Heap* heap) {
    return FreeMovingAction::init_(heap);
}

void ForkFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    FreeMovingAction::enter_(params);
}

void ForkFreeMoving::leave_() {
    FreeMovingAction::leave_();
}

void ForkFreeMoving::loadParams_() {
    FreeMovingAction::loadParams_();
}

void ForkFreeMoving::calc_() {
    FreeMovingAction::calc_();
}

}  // namespace uking::action
