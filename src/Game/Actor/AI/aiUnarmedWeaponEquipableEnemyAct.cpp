#include "Game/Actor/AI/aiUnarmedWeaponEquipableEnemyAct.h"

namespace uking::ai {

UnarmedWeaponEquipableEnemyAct::UnarmedWeaponEquipableEnemyAct(const InitArg& arg)
    : EnemySearch(arg) {}

UnarmedWeaponEquipableEnemyAct::~UnarmedWeaponEquipableEnemyAct() = default;

bool UnarmedWeaponEquipableEnemyAct::init_(sead::Heap* heap) {
    return EnemySearch::init_(heap);
}

void UnarmedWeaponEquipableEnemyAct::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemySearch::enter_(params);
}

void UnarmedWeaponEquipableEnemyAct::leave_() {
    EnemySearch::leave_();
}

void UnarmedWeaponEquipableEnemyAct::loadParams_() {
    EnemySearch::loadParams_();
}

}  // namespace uking::ai
