#include "Game/Actor/AI/aiPriestBossIronBallRoot.h"

namespace uking::ai {

PriestBossIronBallRoot::PriestBossIronBallRoot(const InitArg& arg) : PriestBoss(arg) {}

PriestBossIronBallRoot::~PriestBossIronBallRoot() = default;

bool PriestBossIronBallRoot::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossIronBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossIronBallRoot::leave_() {
    PriestBoss::leave_();
}

void PriestBossIronBallRoot::loadParams_() {
    PriestBoss::loadParams_();
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mMagneLightningTime_s, "MagneLightningTime");
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
