#include "Game/AI/Action/actionTriggerAllPartsSleep.h"

namespace uking::action {

TriggerAllPartsSleep::TriggerAllPartsSleep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TriggerAllPartsSleep::~TriggerAllPartsSleep() = default;

bool TriggerAllPartsSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TriggerAllPartsSleep::loadParams_() {}

}  // namespace uking::action
