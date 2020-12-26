#include "Game/AI/Action/actionReceiveTerror.h"

namespace uking::action {

ReceiveTerror::ReceiveTerror(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReceiveTerror::~ReceiveTerror() = default;

bool ReceiveTerror::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReceiveTerror::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReceiveTerror::leave_() {
    ksys::act::ai::Action::leave_();
}

void ReceiveTerror::loadParams_() {}

void ReceiveTerror::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
