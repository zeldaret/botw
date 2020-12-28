#include "Game/AI/Action/actionXLinkEventFadeAction.h"

namespace uking::action {

XLinkEventFadeAction::XLinkEventFadeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventFadeAction::~XLinkEventFadeAction() = default;

bool XLinkEventFadeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventFadeAction::loadParams_() {
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mSLinkKey_d, "SLinkKey");
}

}  // namespace uking::action
