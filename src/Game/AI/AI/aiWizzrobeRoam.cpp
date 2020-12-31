#include "Game/AI/AI/aiWizzrobeRoam.h"

namespace uking::ai {

WizzrobeRoam::WizzrobeRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeRoam::~WizzrobeRoam() = default;

bool WizzrobeRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeRoam::loadParams_() {
    getStaticParam(&mMoveCountMin_s, "MoveCountMin");
    getStaticParam(&mMoveCountMax_s, "MoveCountMax");
    getStaticParam(&mChangeHeightPer_s, "ChangeHeightPer");
    getStaticParam(&mMexHeightLevel_s, "MexHeightLevel");
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mRetryLength_s, "RetryLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getAITreeVariable(&mWizzrobeMagicWeatherUnit_a, "WizzrobeMagicWeatherUnit");
}

}  // namespace uking::ai
