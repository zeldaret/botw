#include "Game/AI/Action/actionForceRagdollOffWaterFloatFreeze.h"

namespace uking::action {

ForceRagdollOffWaterFloatFreeze::ForceRagdollOffWaterFloatFreeze(const InitArg& arg)
    : WaterFloatFreeze(arg) {}

ForceRagdollOffWaterFloatFreeze::~ForceRagdollOffWaterFloatFreeze() = default;

bool ForceRagdollOffWaterFloatFreeze::init_(sead::Heap* heap) {
    return WaterFloatFreeze::init_(heap);
}

void ForceRagdollOffWaterFloatFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatFreeze::enter_(params);
}

void ForceRagdollOffWaterFloatFreeze::loadParams_() {
    WaterFloatFreeze::loadParams_();
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

}  // namespace uking::action
