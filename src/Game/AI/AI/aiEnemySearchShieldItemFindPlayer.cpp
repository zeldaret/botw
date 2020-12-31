#include "Game/AI/AI/aiEnemySearchShieldItemFindPlayer.h"

namespace uking::ai {

EnemySearchShieldItemFindPlayer::EnemySearchShieldItemFindPlayer(const InitArg& arg)
    : LandHumEnemyFindPlayer(arg) {}

EnemySearchShieldItemFindPlayer::~EnemySearchShieldItemFindPlayer() = default;

bool EnemySearchShieldItemFindPlayer::init_(sead::Heap* heap) {
    return LandHumEnemyFindPlayer::init_(heap);
}

void EnemySearchShieldItemFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyFindPlayer::enter_(params);
}

void EnemySearchShieldItemFindPlayer::leave_() {
    LandHumEnemyFindPlayer::leave_();
}

void EnemySearchShieldItemFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
    getStaticParam(&mShieldIdx_s, "ShieldIdx");
    getStaticParam(&mSearchShieldDist_s, "SearchShieldDist");
    getStaticParam(&mNoShieldSearchDist_s, "NoShieldSearchDist");
    getStaticParam(&mSearchObjectDist_s, "SearchObjectDist");
    getStaticParam(&mItemChaseableSpd_s, "ItemChaseableSpd");
    getStaticParam(&mItemChasealeRot_s, "ItemChasealeRot");
    getStaticParam(&mCanGrabHeavy_s, "CanGrabHeavy");
}

}  // namespace uking::ai
