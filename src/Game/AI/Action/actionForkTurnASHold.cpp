#include "Game/AI/Action/actionForkTurnASHold.h"

namespace uking::action {

ForkTurnASHold::ForkTurnASHold(const InitArg& arg) : ForkAlwaysTurn(arg) {}

ForkTurnASHold::~ForkTurnASHold() = default;

bool ForkTurnASHold::init_(sead::Heap* heap) {
    return ForkAlwaysTurn::init_(heap);
}

void ForkTurnASHold::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysTurn::enter_(params);
}

void ForkTurnASHold::leave_() {
    ForkAlwaysTurn::leave_();
}

void ForkTurnASHold::loadParams_() {
    ForkTurn::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkTurnASHold::calc_() {
    ForkAlwaysTurn::calc_();
}

}  // namespace uking::action
