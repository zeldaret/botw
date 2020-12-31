#include "Game/AI/AI/aiEnemyRandomRepeatSideStep.h"

namespace uking::ai {

EnemyRandomRepeatSideStep::EnemyRandomRepeatSideStep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRandomRepeatSideStep::~EnemyRandomRepeatSideStep() = default;

void EnemyRandomRepeatSideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRandomRepeatSideStep::loadParams_() {
    getStaticParam(&mMinRepeatNum_s, "MinRepeatNum");
    getStaticParam(&mMaxRepeatNum_s, "MaxRepeatNum");
    getStaticParam(&mStepDist_s, "StepDist");
    getStaticParam(&mStepAngle_s, "StepAngle");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
