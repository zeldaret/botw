#include "Game/AI/Action/actionXLinkEventEnable.h"

namespace uking::action {

XLinkEventEnable::XLinkEventEnable(const InitArg& arg) : ksys::act::ai::Action(arg) {}

XLinkEventEnable::~XLinkEventEnable() = default;

bool XLinkEventEnable::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void XLinkEventEnable::loadParams_() {
    getDynamicParam(&mIsEnable_d, "IsEnable");
}

}  // namespace uking::action
