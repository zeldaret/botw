#include "Game/AI/Action/actionEnemyRushAttack.h"

namespace uking::action {

EnemyRushAttack::EnemyRushAttack(const InitArg& arg) : RandomMoveAction(arg) {}

EnemyRushAttack::~EnemyRushAttack() = default;

bool EnemyRushAttack::init_(sead::Heap* heap) {
    return RandomMoveAction::init_(heap);
}

void EnemyRushAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void EnemyRushAttack::leave_() {
    RandomMoveAction::leave_();
}

void EnemyRushAttack::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mUpdateTargetPosInterval_s, "UpdateTargetPosInterval");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mDisableUpdateTargetRadius_s, "DisableUpdateTargetRadius");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mMovePredictionRate_s, "MovePredictionRate");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void EnemyRushAttack::calc_() {
    RandomMoveAction::calc_();
}

}  // namespace uking::action
