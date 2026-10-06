#include "Game/Actor/AI/aiAnimalRndMove.h"

namespace uking::ai {

AnimalRndMove::AnimalRndMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRndMove::~AnimalRndMove() = default;

bool AnimalRndMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRndMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalRndMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRndMove::loadParams_() {
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
