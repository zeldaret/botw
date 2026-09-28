#include "Game/Actor/AI/aiEnemyTargetAction.h"

namespace uking::ai {

EnemyTargetAction::EnemyTargetAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyTargetAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyTargetAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyTargetAction::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mActionDist_s, "ActionDist");
    getStaticParam(&mActionDir_s, "ActionDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
