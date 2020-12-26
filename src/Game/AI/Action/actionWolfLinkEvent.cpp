#include "Game/AI/Action/actionWolfLinkEvent.h"

namespace uking::action {

WolfLinkEvent::WolfLinkEvent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WolfLinkEvent::~WolfLinkEvent() = default;

bool WolfLinkEvent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WolfLinkEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WolfLinkEvent::leave_() {
    ksys::act::ai::Action::leave_();
}

void WolfLinkEvent::loadParams_() {
    getDynamicParam(&mAction_d, "Action");
}

void WolfLinkEvent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
