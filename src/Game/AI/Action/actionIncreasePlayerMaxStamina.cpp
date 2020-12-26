#include "Game/AI/Action/actionIncreasePlayerMaxStamina.h"

namespace uking::action {

IncreasePlayerMaxStamina::IncreasePlayerMaxStamina(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

IncreasePlayerMaxStamina::~IncreasePlayerMaxStamina() = default;

bool IncreasePlayerMaxStamina::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreasePlayerMaxStamina::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IncreasePlayerMaxStamina::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreasePlayerMaxStamina::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mIsMoveCenter_d, "IsMoveCenter");
}

void IncreasePlayerMaxStamina::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
