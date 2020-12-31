#include "Game/AI/AI/aiPriestBossIronBallRoot.h"

namespace uking::ai {

PriestBossIronBallRoot::PriestBossIronBallRoot(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossIronBallRoot::~PriestBossIronBallRoot() = default;

bool PriestBossIronBallRoot::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossIronBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossIronBallRoot::leave_() {
    PriestBossMode::leave_();
}

void PriestBossIronBallRoot::loadParams_() {
    PriestBossMode::loadParams_();
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mMagneLightningTime_s, "MagneLightningTime");
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
