#include "Game/Actor/Area/Action/actionFireObserveBase.h"

namespace uking::action {

FireObserveBase::FireObserveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FireObserveBase::~FireObserveBase() = default;

void FireObserveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FireObserveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
