#include "Game/AI/AI/aiUnderWaterDepthSelect.h"

namespace uking::ai {

UnderWaterDepthSelect::UnderWaterDepthSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

UnderWaterDepthSelect::~UnderWaterDepthSelect() = default;

bool UnderWaterDepthSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void UnderWaterDepthSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void UnderWaterDepthSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void UnderWaterDepthSelect::loadParams_() {
    getStaticParam(&mDeepDepth_s, "DeepDepth");
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
    getStaticParam(&mForceDeepChange_s, "ForceDeepChange");
}

}  // namespace uking::ai
