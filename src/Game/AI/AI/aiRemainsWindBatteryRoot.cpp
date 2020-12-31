#include "Game/AI/AI/aiRemainsWindBatteryRoot.h"

namespace uking::ai {

RemainsWindBatteryRoot::RemainsWindBatteryRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWindBatteryRoot::~RemainsWindBatteryRoot() = default;

bool RemainsWindBatteryRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWindBatteryRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWindBatteryRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWindBatteryRoot::loadParams_() {}

}  // namespace uking::ai
