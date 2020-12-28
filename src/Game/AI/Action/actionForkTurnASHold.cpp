#include "Game/AI/Action/actionForkTurnASHold.h"

namespace uking::action {

ForkTurnASHold::ForkTurnASHold(const InitArg& arg) : ForkAlwaysTurn(arg) {}

ForkTurnASHold::~ForkTurnASHold() = default;

void ForkTurnASHold::calc_() {
    ForkAlwaysTurn::calc_();
}

}  // namespace uking::action
