#include "Game/AI/AI/aiFreezeInWaterSelect.h"

namespace uking::ai {

FreezeInWaterSelect::FreezeInWaterSelect(const InitArg& arg) : InWaterSelect(arg) {}

FreezeInWaterSelect::~FreezeInWaterSelect() = default;

void FreezeInWaterSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    InWaterSelect::enter_(params);
}

void FreezeInWaterSelect::leave_() {
    InWaterSelect::leave_();
}

void FreezeInWaterSelect::loadParams_() {
    InWaterSelect::loadParams_();
    getStaticParam(&mIceBreakTime_s, "IceBreakTime");
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
}

}  // namespace uking::ai
