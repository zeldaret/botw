#include "Game/AI/AI/aiChangeWeatherTagRoot.h"

namespace uking::ai {

ChangeWeatherTagRoot::ChangeWeatherTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool ChangeWeatherTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChangeWeatherTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ChangeWeatherTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChangeWeatherTagRoot::loadParams_() {
    getMapUnitParam(&mWeather_m, "Weather");
    getMapUnitParam(&mWeatherEff_m, "WeatherEff");
    getMapUnitParam(&mPaletteSel_m, "PaletteSel");
    getMapUnitParam(&mPSelSpeed_m, "PSelSpeed");
    getMapUnitParam(&mIgnitedLevel_m, "IgnitedLevel");
    getMapUnitParam(&mTemperatureDay_m, "TemperatureDay");
    getMapUnitParam(&mTemperatureNight_m, "TemperatureNight");
    getMapUnitParam(&mTemperatureDirectDay_m, "TemperatureDirectDay");
    getMapUnitParam(&mTemperatureDirectNight_m, "TemperatureDirectNight");
    getMapUnitParam(&mCloudShadowOff_m, "CloudShadowOff");
    getMapUnitParam(&mBluffThunderOff_m, "BluffThunderOff");
    getMapUnitParam(&mFogMinusCorrection_m, "FogMinusCorrection");
}

}  // namespace uking::ai
