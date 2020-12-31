#include "Game/AI/AI/aiWeaponEquipEnemyWakeUp.h"

namespace uking::ai {

WeaponEquipEnemyWakeUp::WeaponEquipEnemyWakeUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponEquipEnemyWakeUp::~WeaponEquipEnemyWakeUp() = default;

bool WeaponEquipEnemyWakeUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponEquipEnemyWakeUp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponEquipEnemyWakeUp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponEquipEnemyWakeUp::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mWeaponGetRange_s, "WeaponGetRange");
}

}  // namespace uking::ai
