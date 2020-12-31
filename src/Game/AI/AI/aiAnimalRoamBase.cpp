#include "Game/AI/AI/aiAnimalRoamBase.h"

namespace uking::ai {

AnimalRoamBase::AnimalRoamBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRoamBase::~AnimalRoamBase() = default;

bool AnimalRoamBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRoamBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalRoamBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRoamBase::loadParams_() {
    getStaticParam(&mSearchNextPathRadius_s, "SearchNextPathRadius");
    getStaticParam(&mRadiusLimit_s, "RadiusLimit");
    getStaticParam(&mForwardDirDistCoefficient_s, "ForwardDirDistCoefficient");
    getStaticParam(&mDirRandomMinRatio_s, "DirRandomMinRatio");
    getStaticParam(&mDirRangeAngle_s, "DirRangeAngle");
    getStaticParam(&mRejectDistRatio_s, "RejectDistRatio");
    getStaticParam(&mContinueAddSearchAngle_s, "ContinueAddSearchAngle");
    getStaticParam(&mContinueReduceDistRatio_s, "ContinueReduceDistRatio");
    getStaticParam(&mContinueReduceRejectDistRatio_s, "ContinueReduceRejectDistRatio");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
    getMapUnitParam(&mEnableNoEntryAreaCheck_m, "EnableNoEntryAreaCheck");
    getAITreeVariable(&mFramesStuckOnTerrain_a, "FramesStuckOnTerrain");
    getAITreeVariable(&mIsStuckOnTerrain_a, "IsStuckOnTerrain");
}

}  // namespace uking::ai
