#include "Game/AI/AI/aiPriestBossWalkAttack.h"

namespace uking::ai {

PriestBossWalkAttack::PriestBossWalkAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossWalkAttack::~PriestBossWalkAttack() = default;

bool PriestBossWalkAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossWalkAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossWalkAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossWalkAttack::loadParams_() {
    getStaticParam(&mAtDirType_s, "AtDirType");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mAtType_s, "AtType");
    getStaticParam(&mAtShieldBreakPower_s, "AtShieldBreakPower");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mAtPowerReduce_s, "AtPowerReduce");
    getStaticParam(&mAtPower_s, "AtPower");
    getStaticParam(&mAtDamage_s, "AtDamage");
    getStaticParam(&mGoalDistanceTolerance_s, "GoalDistanceTolerance");
    getStaticParam(&mAngleNeedTurn_s, "AngleNeedTurn");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
