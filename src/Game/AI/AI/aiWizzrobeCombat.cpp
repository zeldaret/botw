#include "Game/AI/AI/aiWizzrobeCombat.h"

namespace uking::ai {

WizzrobeCombat::WizzrobeCombat(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeCombat::~WizzrobeCombat() = default;

bool WizzrobeCombat::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeCombat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeCombat::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeCombat::loadParams_() {
    getStaticParam(&mWeatherMagicRate_s, "WeatherMagicRate");
    getStaticParam(&mSummonRate_s, "SummonRate");
    getStaticParam(&mSummonBufferSize_s, "SummonBufferSize");
    getStaticParam(&mMaxHeightLevel_s, "MaxHeightLevel");
    getStaticParam(&mSummonCount_s, "SummonCount");
    getStaticParam(&mAttackLength_s, "AttackLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mSummonBufferKey_s, "SummonBufferKey");
    getStaticParam(&mTargetOffset_s, "TargetOffset");
    getAITreeVariable(&mSummonCount_a, "SummonCount");
    getAITreeVariable(&mIsWizzrobeInBattleAreaFlag_a, "IsWizzrobeInBattleAreaFlag");
}

}  // namespace uking::ai
