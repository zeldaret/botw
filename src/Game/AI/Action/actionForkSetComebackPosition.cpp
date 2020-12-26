#include "Game/AI/Action/actionForkSetComebackPosition.h"

namespace uking::action {

ForkSetComebackPosition::ForkSetComebackPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkSetComebackPosition::~ForkSetComebackPosition() = default;

bool ForkSetComebackPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetComebackPosition::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkSetComebackPosition::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetComebackPosition::loadParams_() {}

void ForkSetComebackPosition::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
