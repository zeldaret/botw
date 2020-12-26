#include "Game/AI/Action/actionXLinkEventEnable.h"

namespace uking::action {

XLinkEventEnable::XLinkEventEnable(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventEnable::~XLinkEventEnable() = default;

bool XLinkEventEnable::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventEnable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void XLinkEventEnable::leave_() {
    ksys::act::ai::Action::leave_();
}

void XLinkEventEnable::loadParams_() {
    getDynamicParam(&mIsEnable_d, "IsEnable");
}

void XLinkEventEnable::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
