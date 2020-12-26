#include "Game/AI/Action/actionAreaFireObserve.h"

namespace uking::action {

AreaFireObserve::AreaFireObserve(const InitArg& arg) : AreaFireObserveBase(arg) {}

AreaFireObserve::~AreaFireObserve() = default;

bool AreaFireObserve::init_(sead::Heap* heap) {
    return AreaFireObserveBase::init_(heap);
}

void AreaFireObserve::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaFireObserveBase::enter_(params);
}

void AreaFireObserve::leave_() {
    AreaFireObserveBase::leave_();
}

void AreaFireObserve::loadParams_() {}

void AreaFireObserve::calc_() {
    AreaFireObserveBase::calc_();
}

}  // namespace uking::action
