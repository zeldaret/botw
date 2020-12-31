#include "Game/AI/AI/aiPriestBossCircleFormationRush.h"

namespace uking::ai {

PriestBossCircleFormationRush::PriestBossCircleFormationRush(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossCircleFormationRush::~PriestBossCircleFormationRush() = default;

bool PriestBossCircleFormationRush::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossCircleFormationRush::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
}

void PriestBossCircleFormationRush::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossCircleFormationRush::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mHomingAttackTime_s, "HomingAttackTime");
}

}  // namespace uking::ai
