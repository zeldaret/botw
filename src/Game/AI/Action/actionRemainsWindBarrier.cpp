#include "Game/AI/Action/actionRemainsWindBarrier.h"

namespace uking::action {

RemainsWindBarrier::RemainsWindBarrier(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RemainsWindBarrier::~RemainsWindBarrier() = default;

bool RemainsWindBarrier::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsWindBarrier::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsWindBarrier::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsWindBarrier::loadParams_() {}

void RemainsWindBarrier::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
