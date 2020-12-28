#include "Game/AI/Action/actionNotStopXLinkWithDemoVisibleOff.h"

namespace uking::action {

NotStopXLinkWithDemoVisibleOff::NotStopXLinkWithDemoVisibleOff(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NotStopXLinkWithDemoVisibleOff::~NotStopXLinkWithDemoVisibleOff() = default;

void NotStopXLinkWithDemoVisibleOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NotStopXLinkWithDemoVisibleOff::leave_() {
    ksys::act::ai::Action::leave_();
}

}  // namespace uking::action
