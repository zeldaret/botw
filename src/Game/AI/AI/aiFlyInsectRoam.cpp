#include "Game/AI/AI/aiFlyInsectRoam.h"

namespace uking::ai {

FlyInsectRoam::FlyInsectRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FlyInsectRoam::~FlyInsectRoam() = default;

bool FlyInsectRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FlyInsectRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FlyInsectRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyInsectRoam::loadParams_() {
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRand_s, "TerritoryRadiusRand");
    getStaticParam(&mMinHeight_s, "MinHeight");
    getStaticParam(&mMaxHeight_s, "MaxHeight");
    getStaticParam(&mRePathDist_s, "RePathDist");
    getStaticParam(&mRePathDistRand_s, "RePathDistRand");
    getStaticParam(&mRePathYDistRand_s, "RePathYDistRand");
    getStaticParam(&mMaxRotRand_s, "MaxRotRand");
    getStaticParam(&mMaxRotRandOuter_s, "MaxRotRandOuter");
    getStaticParam(&mIsEnableOnLand_s, "IsEnableOnLand");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
