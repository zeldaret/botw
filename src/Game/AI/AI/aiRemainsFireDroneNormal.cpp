#include "Game/AI/AI/aiRemainsFireDroneNormal.h"

namespace uking::ai {

RemainsFireDroneNormal::RemainsFireDroneNormal(const InitArg& arg) : RailMove(arg) {}

RemainsFireDroneNormal::~RemainsFireDroneNormal() = default;

bool RemainsFireDroneNormal::init_(sead::Heap* heap) {
    return RailMove::init_(heap);
}

void RemainsFireDroneNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMove::enter_(params);
}

void RemainsFireDroneNormal::leave_() {
    RailMove::leave_();
}

void RemainsFireDroneNormal::loadParams_() {
    RailMove::loadParams_();
    getStaticParam(&mLightLengthOffset_s, "LightLengthOffset");
    getStaticParam(&mAdjustRadius_s, "AdjustRadius");
    getMapUnitParam(&mSearchLightType_m, "SearchLightType");
    getMapUnitParam(&mLightRadius_m, "LightRadius");
    getMapUnitParam(&mLightLength_m, "LightLength");
    getAITreeVariable(&mTargetSpeed_a, "TargetSpeed");
}

}  // namespace uking::ai
