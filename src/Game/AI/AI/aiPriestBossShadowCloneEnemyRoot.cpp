#include "Game/AI/AI/aiPriestBossShadowCloneEnemyRoot.h"

namespace uking::ai {

PriestBossShadowCloneEnemyRoot::PriestBossShadowCloneEnemyRoot(const InitArg& arg)
    : PriestBossActorEnemyRoot(arg) {}

PriestBossShadowCloneEnemyRoot::~PriestBossShadowCloneEnemyRoot() = default;

bool PriestBossShadowCloneEnemyRoot::init_(sead::Heap* heap) {
    return PriestBossActorEnemyRoot::init_(heap);
}

void PriestBossShadowCloneEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorEnemyRoot::enter_(params);
}

void PriestBossShadowCloneEnemyRoot::leave_() {
    PriestBossActorEnemyRoot::leave_();
}

void PriestBossShadowCloneEnemyRoot::loadParams_() {
    PriestBossActorEnemyRoot::loadParams_();
}

}  // namespace uking::ai
