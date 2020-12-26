#include "Game/AI/Action/actionXLinkEventKillAction.h"

namespace uking::action {

XLinkEventKillAction::XLinkEventKillAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventKillAction::~XLinkEventKillAction() = default;

bool XLinkEventKillAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventKillAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void XLinkEventKillAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void XLinkEventKillAction::loadParams_() {
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mSLinkKey_d, "SLinkKey");
}

void XLinkEventKillAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
