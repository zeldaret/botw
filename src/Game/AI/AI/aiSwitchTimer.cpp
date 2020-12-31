#include "Game/AI/AI/aiSwitchTimer.h"

namespace uking::ai {

SwitchTimer::SwitchTimer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchTimer::~SwitchTimer() = default;

bool SwitchTimer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwitchTimer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTimer::loadParams_() {
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

}  // namespace uking::ai
