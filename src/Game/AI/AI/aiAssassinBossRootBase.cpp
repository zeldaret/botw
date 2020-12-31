#include "Game/AI/AI/aiAssassinBossRootBase.h"

namespace uking::ai {

AssassinBossRootBase::AssassinBossRootBase(const InitArg& arg) : EnemyRoot(arg) {}

AssassinBossRootBase::~AssassinBossRootBase() = default;

bool AssassinBossRootBase::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void AssassinBossRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void AssassinBossRootBase::leave_() {
    EnemyRoot::leave_();
}

void AssassinBossRootBase::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mChangeModeLifeRatio_s, "ChangeModeLifeRatio");
    getStaticParam(&mRockBallDamage_s, "RockBallDamage");
}

}  // namespace uking::ai
