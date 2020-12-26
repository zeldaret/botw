#include "Game/AI/Action/actionNotStopXLinkWithDemoVisibleOff.h"

namespace uking::action {

NotStopXLinkWithDemoVisibleOff::NotStopXLinkWithDemoVisibleOff(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NotStopXLinkWithDemoVisibleOff::~NotStopXLinkWithDemoVisibleOff() = default;

bool NotStopXLinkWithDemoVisibleOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NotStopXLinkWithDemoVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NotStopXLinkWithDemoVisibleOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void NotStopXLinkWithDemoVisibleOff::loadParams_() {}

void NotStopXLinkWithDemoVisibleOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
