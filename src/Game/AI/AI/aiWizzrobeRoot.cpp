#include "Game/AI/AI/aiWizzrobeRoot.h"

namespace uking::ai {

WizzrobeRoot::WizzrobeRoot(const InitArg& arg) : EnemyRoot(arg) {}

WizzrobeRoot::~WizzrobeRoot() = default;

bool WizzrobeRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void WizzrobeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void WizzrobeRoot::leave_() {
    EnemyRoot::leave_();
}

void WizzrobeRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mMagicTargetIdx_s, "MagicTargetIdx");
    getStaticParam(&mStartASName_s, "StartASName");
    getStaticParam(&mStopASName_s, "StopASName");
    getAITreeVariable(&mWizzrobeMagicWeatherUnit_a, "WizzrobeMagicWeatherUnit");
}

}  // namespace uking::ai
