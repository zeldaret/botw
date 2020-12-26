#include "Game/AI/Action/actionForkOnEnterCharCtrlInvalid.h"

namespace uking::action {

ForkOnEnterCharCtrlInvalid::ForkOnEnterCharCtrlInvalid(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkOnEnterCharCtrlInvalid::~ForkOnEnterCharCtrlInvalid() = default;

bool ForkOnEnterCharCtrlInvalid::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnEnterCharCtrlInvalid::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkOnEnterCharCtrlInvalid::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOnEnterCharCtrlInvalid::loadParams_() {}

void ForkOnEnterCharCtrlInvalid::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
