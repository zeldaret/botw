#include "Game/AI/Action/actionHoldArrowTurn.h"

namespace uking::action {

HoldArrowTurn::HoldArrowTurn(const InitArg& arg) : TurnBase(arg) {}

HoldArrowTurn::~HoldArrowTurn() = default;

bool HoldArrowTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

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
