#include "Game/AI/AI/aiWizzrobeWeatherMagic.h"

namespace uking::ai {

WizzrobeWeatherMagic::WizzrobeWeatherMagic(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeWeatherMagic::~WizzrobeWeatherMagic() = default;

bool WizzrobeWeatherMagic::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeWeatherMagic::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeWeatherMagic::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeWeatherMagic::loadParams_() {
    getStaticParam(&mRiseLength_s, "RiseLength");
    getStaticParam(&mTimer_s, "Timer");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mWizzrobeMagicWeatherUnit_a, "WizzrobeMagicWeatherUnit");
}

}  // namespace uking::ai
