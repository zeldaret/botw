#include "Game/AI/Action/actionAlertNearbyEnemies.h"

namespace uking::action {

AlertNearbyEnemies::AlertNearbyEnemies(const InitArg& arg) : PlayASForAnimalUnit(arg) {}

AlertNearbyEnemies::~AlertNearbyEnemies() = default;

bool AlertNearbyEnemies::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void AlertNearbyEnemies::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForAnimalUnit::enter_(params);
}

void AlertNearbyEnemies::leave_() {
    PlayASForAnimalUnit::leave_();
}

void AlertNearbyEnemies::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
    getStaticParam(&mAlertRange_s, "AlertRange");
    getStaticParam(&mAlertTime_s, "AlertTime");
    getStaticParam(&mNoiseLevel_s, "NoiseLevel");
    getStaticParam(&mUseNoise_s, "UseNoise");
}

void AlertNearbyEnemies::calc_() {
    PlayASForAnimalUnit::calc_();
}

}  // namespace uking::action
