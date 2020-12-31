#include "Game/AI/AI/aiWeatherReactionCheck.h"

namespace uking::ai {

WeatherReactionCheck::WeatherReactionCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeatherReactionCheck::~WeatherReactionCheck() = default;

bool WeatherReactionCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeatherReactionCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeatherReactionCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeatherReactionCheck::loadParams_() {
    getStaticParam(&mRandTime_s, "RandTime");
    getStaticParam(&mIsReactionRain_s, "IsReactionRain");
    getStaticParam(&mIsReactionSnow_s, "IsReactionSnow");
    getStaticParam(&mIsReturnNormal_s, "IsReturnNormal");
    getStaticParam(&mIsForceChangeable_s, "IsForceChangeable");
}

}  // namespace uking::ai
