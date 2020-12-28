#include "Game/AI/Action/actionStartStaminaUpDemo.h"

namespace uking::action {

StartStaminaUpDemo::StartStaminaUpDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartStaminaUpDemo::~StartStaminaUpDemo() = default;

bool StartStaminaUpDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartStaminaUpDemo::loadParams_() {}

}  // namespace uking::action
