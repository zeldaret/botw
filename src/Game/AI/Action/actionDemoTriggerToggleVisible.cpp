#include "Game/AI/Action/actionDemoTriggerToggleVisible.h"

namespace uking::action {

DemoTriggerToggleVisible::DemoTriggerToggleVisible(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoTriggerToggleVisible::~DemoTriggerToggleVisible() = default;

bool DemoTriggerToggleVisible::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoTriggerToggleVisible::loadParams_() {
    getDynamicParam(&mIsVisible_d, "IsVisible");
    getDynamicParam(&mIsXLinkHandling_d, "IsXLinkHandling");
    getDynamicParam(&mIsClothHandling_d, "IsClothHandling");
}

}  // namespace uking::action
