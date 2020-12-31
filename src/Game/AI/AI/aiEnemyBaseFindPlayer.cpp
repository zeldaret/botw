#include "Game/AI/AI/aiEnemyBaseFindPlayer.h"

namespace uking::ai {

EnemyBaseFindPlayer::EnemyBaseFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyBaseFindPlayer::~EnemyBaseFindPlayer() = default;

bool EnemyBaseFindPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyBaseFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyBaseFindPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyBaseFindPlayer::loadParams_() {
    getStaticParam(&mSurpriseAttackPer_s, "SurpriseAttackPer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mSurpriseAttackTime_s, "SurpriseAttackTime");
    getStaticParam(&mSurpriseAttackTimeRand_s, "SurpriseAttackTimeRand");
    getStaticParam(&mRerouteTimeMin_s, "RerouteTimeMin");
    getStaticParam(&mRerouteTimeMax_s, "RerouteTimeMax");
    getStaticParam(&mRestreintTime_s, "RestreintTime");
    getStaticParam(&mRetTiredFromTime_s, "RetTiredFromTime");
    getStaticParam(&mSurpriseAttackRange_s, "SurpriseAttackRange");
    getStaticParam(&mAttackRange_s, "AttackRange");
    getStaticParam(&mAttackVMin_s, "AttackVMin");
    getStaticParam(&mAttackVMax_s, "AttackVMax");
    getStaticParam(&mSwiftAttackVMin_s, "SwiftAttackVMin");
    getStaticParam(&mSwiftAttackVMax_s, "SwiftAttackVMax");
    getStaticParam(&mRestreintTiredDist_s, "RestreintTiredDist");
    getStaticParam(&mForceFirstAttackDist_s, "ForceFirstAttackDist");
    getStaticParam(&mRetForceFirstAttackDist_s, "RetForceFirstAttackDist");
    getStaticParam(&mPathTooLongDist_s, "PathTooLongDist");
    getStaticParam(&mNoSearchFromTiredDist_s, "NoSearchFromTiredDist");
    getAITreeVariable(&mIsTryingReturnRestreint_a, "IsTryingReturnRestreint");
}

}  // namespace uking::ai
