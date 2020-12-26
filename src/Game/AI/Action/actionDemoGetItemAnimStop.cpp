#include "Game/AI/Action/actionDemoGetItemAnimStop.h"

namespace uking::action {

DemoGetItemAnimStop::DemoGetItemAnimStop(const InitArg& arg) : DemoGetItem(arg) {}

DemoGetItemAnimStop::~DemoGetItemAnimStop() = default;

bool DemoGetItemAnimStop::init_(sead::Heap* heap) {
    return DemoGetItem::init_(heap);
}

void DemoGetItemAnimStop::enter_(ksys::act::ai::InlineParamPack* params) {
    DemoGetItem::enter_(params);
}

void DemoGetItemAnimStop::leave_() {
    DemoGetItem::leave_();
}

void DemoGetItemAnimStop::loadParams_() {
    DemoGetItem::loadParams_();
    getStaticParam(&mWaitASKeyName_s, "WaitASKeyName");
}

void DemoGetItemAnimStop::calc_() {
    DemoGetItem::calc_();
}

}  // namespace uking::action
