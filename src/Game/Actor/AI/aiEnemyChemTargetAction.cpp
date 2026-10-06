#include "Game/Actor/AI/aiEnemyChemTargetAction.h"

namespace uking::ai {

EnemyChemTargetAction::EnemyChemTargetAction(const InitArg& arg) : EnemyTargetAction(arg) {}

EnemyChemTargetAction::~EnemyChemTargetAction() = default;

bool EnemyChemTargetAction::init_(sead::Heap* heap) {
    return EnemyTargetAction::init_(heap);
}

void EnemyChemTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyTargetAction::enter_(params);
}

void EnemyChemTargetAction::leave_() {
    EnemyTargetAction::leave_();
}

void EnemyChemTargetAction::loadParams_() {
    EnemyTargetAction::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
