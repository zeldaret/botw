#include "Game/AI/Action/actionWarpPlayerBase.h"

namespace uking::action {

WarpPlayerBase::WarpPlayerBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpPlayerBase::~WarpPlayerBase() = default;

bool WarpPlayerBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpPlayerBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpPlayerBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPlayerBase::loadParams_() {}

void WarpPlayerBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
