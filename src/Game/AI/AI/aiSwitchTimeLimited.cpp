#include "Game/AI/AI/aiSwitchTimeLimited.h"

namespace uking::ai {

SwitchTimeLimited::SwitchTimeLimited(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchTimeLimited::~SwitchTimeLimited() = default;

bool SwitchTimeLimited::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchTimeLimited::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwitchTimeLimited::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTimeLimited::loadParams_() {
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

}  // namespace uking::ai
