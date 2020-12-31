#include "Game/AI/AI/aiWaitForCloseOrWaterSide.h"

namespace uking::ai {

WaitForCloseOrWaterSide::WaitForCloseOrWaterSide(const InitArg& arg) : WaitForTargetClose(arg) {}

WaitForCloseOrWaterSide::~WaitForCloseOrWaterSide() = default;

bool WaitForCloseOrWaterSide::init_(sead::Heap* heap) {
    return WaitForTargetClose::init_(heap);
}

void WaitForCloseOrWaterSide::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitForTargetClose::enter_(params);
}

void WaitForCloseOrWaterSide::leave_() {
    WaitForTargetClose::leave_();
}

void WaitForCloseOrWaterSide::loadParams_() {
    WaitForTargetClose::loadParams_();
    getStaticParam(&mDistFromWater_s, "DistFromWater");
}

}  // namespace uking::ai
