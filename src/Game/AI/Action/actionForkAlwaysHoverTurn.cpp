#include "Game/AI/Action/actionForkAlwaysHoverTurn.h"

namespace uking::action {

ForkAlwaysHoverTurn::ForkAlwaysHoverTurn(const InitArg& arg) : ForkAlwaysTurn(arg) {}

ForkAlwaysHoverTurn::~ForkAlwaysHoverTurn() = default;

bool ForkAlwaysHoverTurn::init_(sead::Heap* heap) {
    return ForkAlwaysTurn::init_(heap);
}

void ForkAlwaysHoverTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysTurn::enter_(params);
}

void ForkAlwaysHoverTurn::leave_() {
    ForkAlwaysTurn::leave_();
}

void ForkAlwaysHoverTurn::loadParams_() {
    ForkAlwaysTurn::loadParams_();
}

void ForkAlwaysHoverTurn::calc_() {
    ForkAlwaysTurn::calc_();
}

}  // namespace uking::action
