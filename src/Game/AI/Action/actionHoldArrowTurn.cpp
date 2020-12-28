#include "Game/AI/Action/actionHoldArrowTurn.h"

namespace uking::action {

HoldArrowTurn::HoldArrowTurn(const InitArg& arg) : TurnBase(arg) {}

void HoldArrowTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void HoldArrowTurn::leave_() {
    TurnBase::leave_();
}

void HoldArrowTurn::loadParams_() {}

void HoldArrowTurn::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
