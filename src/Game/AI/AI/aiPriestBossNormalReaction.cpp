#include "Game/AI/AI/aiPriestBossNormalReaction.h"

namespace uking::ai {

PriestBossNormalReaction::PriestBossNormalReaction(const InitArg& arg)
    : EnemyDefaultReaction(arg) {}

PriestBossNormalReaction::~PriestBossNormalReaction() = default;

bool PriestBossNormalReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void PriestBossNormalReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void PriestBossNormalReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void PriestBossNormalReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsUseQuickRecover_s, "IsUseQuickRecover");
    getAITreeVariable(&mPriestBossUrbosasFuryEShock_a, "PriestBossUrbosasFuryEShock");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
