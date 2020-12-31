#include "Game/AI/AI/aiInWaterSelect.h"

namespace uking::ai {

InWaterSelect::InWaterSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InWaterSelect::~InWaterSelect() = default;

bool InWaterSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InWaterSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void InWaterSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InWaterSelect::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mOutWaterDepth_s, "OutWaterDepth");
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
    getStaticParam(&mIsForceChange_s, "IsForceChange");
}

}  // namespace uking::ai
