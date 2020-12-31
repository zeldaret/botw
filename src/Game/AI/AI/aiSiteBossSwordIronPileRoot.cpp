#include "Game/AI/AI/aiSiteBossSwordIronPileRoot.h"

namespace uking::ai {

SiteBossSwordIronPileRoot::SiteBossSwordIronPileRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSwordIronPileRoot::~SiteBossSwordIronPileRoot() = default;

bool SiteBossSwordIronPileRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSwordIronPileRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSwordIronPileRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSwordIronPileRoot::loadParams_() {
    getStaticParam(&mFallWaitCount_s, "FallWaitCount");
    getStaticParam(&mFallSpeed_s, "FallSpeed");
    getStaticParam(&mSlopeRate_s, "SlopeRate");
    getMapUnitParam(&mAddAtkPower_m, "AddAtkPower");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mActorName_m, "ActorName");
}

}  // namespace uking::ai
