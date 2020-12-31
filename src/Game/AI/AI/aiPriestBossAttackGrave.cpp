#include "Game/AI/AI/aiPriestBossAttackGrave.h"

namespace uking::ai {

PriestBossAttackGrave::PriestBossAttackGrave(const InitArg& arg) : AttackGrave(arg) {}

PriestBossAttackGrave::~PriestBossAttackGrave() = default;

bool PriestBossAttackGrave::init_(sead::Heap* heap) {
    return AttackGrave::init_(heap);
}

void PriestBossAttackGrave::enter_(ksys::act::ai::InlineParamPack* params) {
    AttackGrave::enter_(params);
}

void PriestBossAttackGrave::leave_() {
    AttackGrave::leave_();
}

void PriestBossAttackGrave::loadParams_() {
    AttackGrave::loadParams_();
}

}  // namespace uking::ai
