#include "Game/AI/Action/actionDemoGetItemAnimStop.h"

namespace uking::action {

DemoGetItemAnimStop::DemoGetItemAnimStop(const InitArg& arg) : DemoGetItem(arg) {}

DemoGetItemAnimStop::~DemoGetItemAnimStop() = default;

bool DemoGetItemAnimStop::init_(sead::Heap* heap) {
    return DemoGetItem::init_(heap);
}

void DemoGetItemAnimStop::loadParams_() {
    DemoGetItem::loadParams_();
    getStaticParam(&mWaitASKeyName_s, "WaitASKeyName");
}

}  // namespace uking::action
