#include "Game/AI/Action/actionXLinkEventKillAction.h"

namespace uking::action {

XLinkEventKillAction::XLinkEventKillAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventKillAction::~XLinkEventKillAction() = default;

bool XLinkEventKillAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventKillAction::loadParams_() {
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mSLinkKey_d, "SLinkKey");
}

}  // namespace uking::action
