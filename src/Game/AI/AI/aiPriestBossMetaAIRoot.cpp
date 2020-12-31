#include "Game/AI/AI/aiPriestBossMetaAIRoot.h"

namespace uking::ai {

PriestBossMetaAIRoot::PriestBossMetaAIRoot(const InitArg& arg) : PriestBossMeta(arg) {}

PriestBossMetaAIRoot::~PriestBossMetaAIRoot() = default;

bool PriestBossMetaAIRoot::init_(sead::Heap* heap) {
    return PriestBossMeta::init_(heap);
}

void PriestBossMetaAIRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMeta::enter_(params);
}

void PriestBossMetaAIRoot::leave_() {
    PriestBossMeta::leave_();
}

void PriestBossMetaAIRoot::loadParams_() {
    PriestBossMeta::loadParams_();
    getStaticParam(&mLife_s, "Life");
    getStaticParam(&mPlayerRecoverFromFallFrames_s, "PlayerRecoverFromFallFrames");
    getStaticParam(&mBowActorName_s, "BowActorName");
    getStaticParam(&mArrowActorName_s, "ArrowActorName");
    getStaticParam(&mWeaponActorName_s, "WeaponActorName");
    getStaticParam(&mThunderActorName_s, "ThunderActorName");
    getMapUnitParam(&mPriestBossStartPhase_m, "PriestBossStartPhase");
    getMapUnitParam(&mUniqueNameMessageLabel_m, "UniqueNameMessageLabel");
}

}  // namespace uking::ai
