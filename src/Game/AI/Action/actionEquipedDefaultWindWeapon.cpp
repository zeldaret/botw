#include "Game/AI/Action/actionEquipedDefaultWindWeapon.h"

namespace uking::action {

EquipedDefaultWindWeapon::EquipedDefaultWindWeapon(const InitArg& arg) : EquipedAction(arg) {}

bool EquipedDefaultWindWeapon::init_(sead::Heap* heap) {
    return EquipedAction::init_(heap);
}

void EquipedDefaultWindWeapon::loadParams_() {
    EquipedAction::loadParams_();
    getStaticParam(&mWindRadius_s, "WindRadius");
    getStaticParam(&mWindRadiusLarge_s, "WindRadiusLarge");
    getStaticParam(&mWindSpeed_s, "WindSpeed");
    getStaticParam(&mWindSpeedLarge_s, "WindSpeedLarge");
    getStaticParam(&mWindSpeedRate1_s, "WindSpeedRate1");
    getStaticParam(&mWindSpeedRate2_s, "WindSpeedRate2");
    getStaticParam(&mWindSpeedRate3_s, "WindSpeedRate3");
    getStaticParam(&mWindLength_s, "WindLength");
    getStaticParam(&mCapsuleMaxSpeed_s, "CapsuleMaxSpeed");
    getStaticParam(&mWindReduceRate_s, "WindReduceRate");
    getStaticParam(&mWindReduceRateLarge_s, "WindReduceRateLarge");
    getStaticParam(&mWindFlyingDist_s, "WindFlyingDist");
    getStaticParam(&mWindFlyingDistLarge_s, "WindFlyingDistLarge");
    getStaticParam(&mWindFlyingDistRate1_s, "WindFlyingDistRate1");
    getStaticParam(&mWindFlyingDistRate2_s, "WindFlyingDistRate2");
    getStaticParam(&mWindFlyingDistRate3_s, "WindFlyingDistRate3");
}

void EquipedDefaultWindWeapon::calc_() {
    EquipedAction::calc_();
}

}  // namespace uking::action
