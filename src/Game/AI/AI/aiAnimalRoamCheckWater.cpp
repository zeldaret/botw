#include "Game/AI/AI/aiAnimalRoamCheckWater.h"

namespace uking::ai {

AnimalRoamCheckWater::AnimalRoamCheckWater(const InitArg& arg) : AnimalRoam(arg) {}

AnimalRoamCheckWater::~AnimalRoamCheckWater() = default;

bool AnimalRoamCheckWater::init_(sead::Heap* heap) {
    return AnimalRoam::init_(heap);
}

void AnimalRoamCheckWater::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalRoam::enter_(params);
}

void AnimalRoamCheckWater::leave_() {
    AnimalRoam::leave_();
}

void AnimalRoamCheckWater::loadParams_() {
    AnimalRoam::loadParams_();
    getStaticParam(&mWaterLevelLimitLower_s, "WaterLevelLimitLower");
    getStaticParam(&mWaterLevelLimitUpper_s, "WaterLevelLimitUpper");
}

}  // namespace uking::ai
