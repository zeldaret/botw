#include "Game/AI/AI/aiSwitchTimeLag.h"

namespace uking::ai {

SwitchTimeLag::SwitchTimeLag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwitchTimeLag::~SwitchTimeLag() = default;

bool SwitchTimeLag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwitchTimeLag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwitchTimeLag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwitchTimeLag::loadParams_() {
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

}  // namespace uking::ai
