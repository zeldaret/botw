#include "Game/AI/Action/actionDemoTriggerToggleVisible.h"

namespace uking::action {

DemoTriggerToggleVisible::DemoTriggerToggleVisible(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoTriggerToggleVisible::~DemoTriggerToggleVisible() = default;

bool DemoTriggerToggleVisible::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoTriggerToggleVisible::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoTriggerToggleVisible::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoTriggerToggleVisible::loadParams_() {
    getDynamicParam(&mIsVisible_d, "IsVisible");
    getDynamicParam(&mIsXLinkHandling_d, "IsXLinkHandling");
    getDynamicParam(&mIsClothHandling_d, "IsClothHandling");
}

void DemoTriggerToggleVisible::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
