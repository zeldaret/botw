#include "Game/AI/Action/actionXLinkEventFadeAction.h"

namespace uking::action {

XLinkEventFadeAction::XLinkEventFadeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventFadeAction::~XLinkEventFadeAction() = default;

bool XLinkEventFadeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventFadeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void XLinkEventFadeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void XLinkEventFadeAction::loadParams_() {
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mSLinkKey_d, "SLinkKey");
}

void XLinkEventFadeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
