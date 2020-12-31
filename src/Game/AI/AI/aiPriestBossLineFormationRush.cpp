#include "Game/AI/AI/aiPriestBossLineFormationRush.h"

namespace uking::ai {

PriestBossLineFormationRush::PriestBossLineFormationRush(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossLineFormationRush::~PriestBossLineFormationRush() = default;

bool PriestBossLineFormationRush::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossLineFormationRush::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
}

void PriestBossLineFormationRush::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossLineFormationRush::loadParams_() {
    PriestBossFormation::loadParams_();
}

}  // namespace uking::ai
