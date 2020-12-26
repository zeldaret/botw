#include "Game/AI/Action/actionChangeEnvForEnduranceDungeon.h"

namespace uking::action {

ChangeEnvForEnduranceDungeon::ChangeEnvForEnduranceDungeon(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ChangeEnvForEnduranceDungeon::~ChangeEnvForEnduranceDungeon() = default;

bool ChangeEnvForEnduranceDungeon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeEnvForEnduranceDungeon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangeEnvForEnduranceDungeon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeEnvForEnduranceDungeon::loadParams_() {
    getMapUnitParam(&mWeather_m, "Weather");
    getMapUnitParam(&mIgnitedLevel_m, "IgnitedLevel");
    getMapUnitParam(&mWeatherEff_m, "WeatherEff");
    getMapUnitParam(&mPaletteSel_m, "PaletteSel");
    getMapUnitParam(&mTimeForSkyEnv_m, "TimeForSkyEnv");
    getMapUnitParam(&mTemperatureDirectDay_m, "TemperatureDirectDay");
    getMapUnitParam(&mTemperatureDirectNight_m, "TemperatureDirectNight");
}

void ChangeEnvForEnduranceDungeon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
