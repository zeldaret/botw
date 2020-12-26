#include "Game/AI/Action/actionForkAlwaysTurn.h"

namespace uking::action {

ForkAlwaysTurn::ForkAlwaysTurn(const InitArg& arg) : ForkTurn(arg) {}

ForkAlwaysTurn::~ForkAlwaysTurn() = default;

bool ForkAlwaysTurn::init_(sead::Heap* heap) {
    return ForkTurn::init_(heap);
}

void ForkAlwaysTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkTurn::enter_(params);
}

void ForkAlwaysTurn::leave_() {
    ForkTurn::leave_();
}

void ForkAlwaysTurn::loadParams_() {
    ForkTurn::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkAlwaysTurn::calc_() {
    ForkTurn::calc_();
}

}  // namespace uking::action
