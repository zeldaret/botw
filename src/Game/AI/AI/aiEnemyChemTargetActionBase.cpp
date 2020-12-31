#include "Game/AI/AI/aiEnemyChemTargetActionBase.h"

namespace uking::ai {

EnemyChemTargetActionBase::EnemyChemTargetActionBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyChemTargetActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyChemTargetActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyChemTargetActionBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyChemTargetActionBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mActionDist_s, "ActionDist");
    getStaticParam(&mActionDir_s, "ActionDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
