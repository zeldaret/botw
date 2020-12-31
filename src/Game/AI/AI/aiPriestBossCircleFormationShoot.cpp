#include "Game/AI/AI/aiPriestBossCircleFormationShoot.h"

namespace uking::ai {

PriestBossCircleFormationShoot::PriestBossCircleFormationShoot(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossCircleFormationShoot::~PriestBossCircleFormationShoot() = default;

bool PriestBossCircleFormationShoot::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossCircleFormationShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
}

void PriestBossCircleFormationShoot::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossCircleFormationShoot::loadParams_() {
    PriestBossFormation::loadParams_();
    getStaticParam(&mHomingAttackTime_s, "HomingAttackTime");
}

}  // namespace uking::ai
