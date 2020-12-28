#include "Game/AI/Action/actionDemoGetItem.h"

namespace uking::action {

DemoGetItem::DemoGetItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoGetItem::~DemoGetItem() = default;

bool DemoGetItem::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoGetItem::loadParams_() {}

}  // namespace uking::action
