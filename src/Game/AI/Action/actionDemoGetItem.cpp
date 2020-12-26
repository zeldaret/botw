#include "Game/AI/Action/actionDemoGetItem.h"

namespace uking::action {

DemoGetItem::DemoGetItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoGetItem::~DemoGetItem() = default;

bool DemoGetItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoGetItem::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoGetItem::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoGetItem::loadParams_() {}

void DemoGetItem::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
