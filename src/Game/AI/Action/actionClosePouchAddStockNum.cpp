#include "Game/AI/Action/actionClosePouchAddStockNum.h"

namespace uking::action {

ClosePouchAddStockNum::ClosePouchAddStockNum(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ClosePouchAddStockNum::~ClosePouchAddStockNum() = default;

bool ClosePouchAddStockNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ClosePouchAddStockNum::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ClosePouchAddStockNum::leave_() {
    ksys::act::ai::Action::leave_();
}

void ClosePouchAddStockNum::loadParams_() {}

void ClosePouchAddStockNum::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
