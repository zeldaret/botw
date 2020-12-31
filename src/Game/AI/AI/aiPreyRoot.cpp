#include "Game/AI/AI/aiPreyRoot.h"

namespace uking::ai {

PreyRoot::PreyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyRoot::~PreyRoot() = default;

bool PreyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyRoot::loadParams_() {
    getStaticParam(&mAfterEscapeForceEndState_s, "AfterEscapeForceEndState");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mEscapeForceEndTime_s, "EscapeForceEndTime");
    getStaticParam(&mIsCheckFreeFall_s, "IsCheckFreeFall");
    getStaticParam(&mIsCheckStuckConsiderY_s, "IsCheckStuckConsiderY");
    getStaticParam(&mIsUseWeakForcePushOutside_s, "IsUseWeakForcePushOutside");
    getStaticParam(&mIsEnableEscapeForceEndCheck_s, "IsEnableEscapeForceEndCheck");
    getAITreeVariable(&mCreateDeadConditionType_a, "CreateDeadConditionType");
    getAITreeVariable(&mFramesStuckOnTerrain_a, "FramesStuckOnTerrain");
    getAITreeVariable(&mIsStuckOnTerrain_a, "IsStuckOnTerrain");
    getAITreeVariable(&mIsChangeableStateFreeFall_a, "IsChangeableStateFreeFall");
    getAITreeVariable(&mIsUseTerritory_a, "IsUseTerritory");
}

}  // namespace uking::ai
