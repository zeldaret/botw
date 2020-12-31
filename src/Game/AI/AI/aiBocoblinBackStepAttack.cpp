#include "Game/AI/AI/aiBocoblinBackStepAttack.h"

namespace uking::ai {

BocoblinBackStepAttack::BocoblinBackStepAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BocoblinBackStepAttack::~BocoblinBackStepAttack() = default;

void BocoblinBackStepAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BocoblinBackStepAttack::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mAttackPer_d, "AttackPer");
}

}  // namespace uking::ai
