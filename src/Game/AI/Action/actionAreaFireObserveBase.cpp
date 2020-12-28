#include "Game/AI/Action/actionAreaFireObserveBase.h"

namespace uking::action {

AreaFireObserveBase::AreaFireObserveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaFireObserveBase::~AreaFireObserveBase() = default;

void AreaFireObserveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AreaFireObserveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
