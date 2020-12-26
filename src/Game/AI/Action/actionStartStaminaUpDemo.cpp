#include "Game/AI/Action/actionStartStaminaUpDemo.h"

namespace uking::action {

StartStaminaUpDemo::StartStaminaUpDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartStaminaUpDemo::~StartStaminaUpDemo() = default;

bool StartStaminaUpDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartStaminaUpDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StartStaminaUpDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void StartStaminaUpDemo::loadParams_() {}

void StartStaminaUpDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
