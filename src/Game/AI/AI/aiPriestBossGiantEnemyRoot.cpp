#include "Game/AI/AI/aiPriestBossGiantEnemyRoot.h"

namespace uking::ai {

PriestBossGiantEnemyRoot::PriestBossGiantEnemyRoot(const InitArg& arg)
    : PriestBossActorEnemyRoot(arg) {}

PriestBossGiantEnemyRoot::~PriestBossGiantEnemyRoot() = default;

bool PriestBossGiantEnemyRoot::init_(sead::Heap* heap) {
    return PriestBossActorEnemyRoot::init_(heap);
}

void PriestBossGiantEnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorEnemyRoot::enter_(params);
}

void PriestBossGiantEnemyRoot::leave_() {
    PriestBossActorEnemyRoot::leave_();
}

void PriestBossGiantEnemyRoot::loadParams_() {
    PriestBossActorEnemyRoot::loadParams_();
    getStaticParam(&mInvalidateIronBallDamageFrame_s, "InvalidateIronBallDamageFrame");
    getAITreeVariable(&mPriestBossDownSideASPlaying_a, "PriestBossDownSideASPlaying");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
