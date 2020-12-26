#include "Game/AI/Action/actionTriggerAllPartsSleep.h"

namespace uking::action {

TriggerAllPartsSleep::TriggerAllPartsSleep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TriggerAllPartsSleep::~TriggerAllPartsSleep() = default;

bool TriggerAllPartsSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TriggerAllPartsSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TriggerAllPartsSleep::leave_() {
    ksys::act::ai::Action::leave_();
}

void TriggerAllPartsSleep::loadParams_() {}

void TriggerAllPartsSleep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
