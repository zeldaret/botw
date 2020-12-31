#include "Game/AI/AI/aiAnimalEscapeAI.h"

namespace uking::ai {

AnimalEscapeAI::AnimalEscapeAI(const InitArg& arg) : AnimalRoamBase(arg) {}

AnimalEscapeAI::~AnimalEscapeAI() = default;

bool AnimalEscapeAI::init_(sead::Heap* heap) {
    return AnimalRoamBase::init_(heap);
}

void AnimalEscapeAI::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalRoamBase::enter_(params);
}

void AnimalEscapeAI::leave_() {
    AnimalRoamBase::leave_();
}

void AnimalEscapeAI::loadParams_() {
    AnimalRoamBase::loadParams_();
    getStaticParam(&mNumTimesAllowStuck_s, "NumTimesAllowStuck");
    getStaticParam(&mContinueDistance_s, "ContinueDistance");
    getStaticParam(&mShouldEscapeDistance_s, "ShouldEscapeDistance");
    getStaticParam(&mShouldEscapeDistanceRand_s, "ShouldEscapeDistanceRand");
    getStaticParam(&mPenaltyScale_s, "PenaltyScale");
    getStaticParam(&mNavMeshRadiusScale_s, "NavMeshRadiusScale");
    getStaticParam(&mFramesStuckOnTerrainAction_s, "FramesStuckOnTerrainAction");
    getStaticParam(&mIsSendGoalPos_s, "IsSendGoalPos");
    getStaticParam(&mIsUseBeforeAction_s, "IsUseBeforeAction");
    getStaticParam(&mIsDynamicallyOffsetNavChar_s, "IsDynamicallyOffsetNavChar");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mIsUseTerritory_a, "IsUseTerritory");
}

}  // namespace uking::ai
