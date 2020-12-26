#include "Game/AI/Action/actionXLinkEventCreateAction.h"

namespace uking::action {

XLinkEventCreateAction::XLinkEventCreateAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventCreateAction::~XLinkEventCreateAction() = default;

bool XLinkEventCreateAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventCreateAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void XLinkEventCreateAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void XLinkEventCreateAction::loadParams_() {
    getDynamicParam(&mIsTargetDemoSLinkUser_d, "IsTargetDemoSLinkUser");
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mSLinkKey_d, "SLinkKey");
}

void XLinkEventCreateAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
