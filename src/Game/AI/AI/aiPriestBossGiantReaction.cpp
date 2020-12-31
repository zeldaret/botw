#include "Game/AI/AI/aiPriestBossGiantReaction.h"

namespace uking::ai {

PriestBossGiantReaction::PriestBossGiantReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

PriestBossGiantReaction::~PriestBossGiantReaction() = default;

bool PriestBossGiantReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void PriestBossGiantReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void PriestBossGiantReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void PriestBossGiantReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getAITreeVariable(&mPriestBossUrbosasFuryEShock_a, "PriestBossUrbosasFuryEShock");
}

}  // namespace uking::ai
