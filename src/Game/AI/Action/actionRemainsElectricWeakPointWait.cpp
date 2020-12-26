#include "Game/AI/Action/actionRemainsElectricWeakPointWait.h"

namespace uking::action {

RemainsElectricWeakPointWait::RemainsElectricWeakPointWait(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsElectricWeakPointWait::~RemainsElectricWeakPointWait() = default;

bool RemainsElectricWeakPointWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsElectricWeakPointWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsElectricWeakPointWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsElectricWeakPointWait::loadParams_() {}

void RemainsElectricWeakPointWait::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
