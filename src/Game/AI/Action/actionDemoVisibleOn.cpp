#include "Game/AI/Action/actionDemoVisibleOn.h"

namespace uking::action {

DemoVisibleOn::DemoVisibleOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVisibleOn::~DemoVisibleOn() = default;

bool DemoVisibleOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoVisibleOn::loadParams_() {}

}  // namespace uking::action
