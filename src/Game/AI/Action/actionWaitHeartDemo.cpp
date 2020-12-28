#include "Game/AI/Action/actionWaitHeartDemo.h"

namespace uking::action {

WaitHeartDemo::WaitHeartDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitHeartDemo::~WaitHeartDemo() = default;

bool WaitHeartDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitHeartDemo::loadParams_() {}

}  // namespace uking::action
