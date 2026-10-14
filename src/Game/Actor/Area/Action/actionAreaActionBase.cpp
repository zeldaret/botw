#include "Game/Actor/Area/Action/actionAreaActionBase.h"

namespace uking::action {

AreaActionBase::AreaActionBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaActionBase::~AreaActionBase() = default;

void AreaActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AreaActionBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
