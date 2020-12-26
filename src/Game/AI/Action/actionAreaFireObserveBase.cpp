#include "Game/AI/Action/actionAreaFireObserveBase.h"

namespace uking::action {

AreaFireObserveBase::AreaFireObserveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaFireObserveBase::~AreaFireObserveBase() = default;

bool AreaFireObserveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AreaFireObserveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AreaFireObserveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AreaFireObserveBase::loadParams_() {}

void AreaFireObserveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
