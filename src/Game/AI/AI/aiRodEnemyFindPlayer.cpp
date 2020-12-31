#include "Game/AI/AI/aiRodEnemyFindPlayer.h"

namespace uking::ai {

RodEnemyFindPlayer::RodEnemyFindPlayer(const InitArg& arg) : LandHumEnemyFindPlayer(arg) {}

RodEnemyFindPlayer::~RodEnemyFindPlayer() = default;

bool RodEnemyFindPlayer::init_(sead::Heap* heap) {
    return LandHumEnemyFindPlayer::init_(heap);
}

void RodEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyFindPlayer::enter_(params);
}

void RodEnemyFindPlayer::leave_() {
    LandHumEnemyFindPlayer::leave_();
}

void RodEnemyFindPlayer::loadParams_() {
    LandHumEnemyFindPlayer::loadParams_();
    getStaticParam(&mMagicPer_s, "MagicPer");
    getStaticParam(&mMagicIntervalIntensity_s, "MagicIntervalIntensity");
    getStaticParam(&mMagicCheckInterval_s, "MagicCheckInterval");
    getStaticParam(&mRodWeaponIdx_s, "RodWeaponIdx");
    getStaticParam(&mMagicAttackDir_s, "MagicAttackDir");
}

}  // namespace uking::ai
