#include "Game/AI/Action/actionEnemyChangeWeapon.h"

namespace uking::action {

EnemyChangeWeapon::EnemyChangeWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EnemyChangeWeapon::~EnemyChangeWeapon() = default;

bool EnemyChangeWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyChangeWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnemyChangeWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnemyChangeWeapon::loadParams_() {
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

void EnemyChangeWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
