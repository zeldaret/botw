#include "Game/AI/AI/aiPriestBossActorEnemyRoot.h"

namespace uking::ai {

PriestBossActorEnemyRoot::PriestBossActorEnemyRoot(const InitArg& arg) : EnemyRoot(arg) {}

PriestBossActorEnemyRoot::~PriestBossActorEnemyRoot() = default;

bool PriestBossActorEnemyRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void PriestBossActorEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void PriestBossActorEnemyRoot::leave_() {
    EnemyRoot::leave_();
}

void PriestBossActorEnemyRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mIsReactionOnDead_s, "IsReactionOnDead");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
