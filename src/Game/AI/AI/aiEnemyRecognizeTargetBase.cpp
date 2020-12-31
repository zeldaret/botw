#include "Game/AI/AI/aiEnemyRecognizeTargetBase.h"

namespace uking::ai {

EnemyRecognizeTargetBase::EnemyRecognizeTargetBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRecognizeTargetBase::~EnemyRecognizeTargetBase() = default;

bool EnemyRecognizeTargetBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRecognizeTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRecognizeTargetBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRecognizeTargetBase::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCryInterval_s, "CryInterval");
    getStaticParam(&mRandomCryInterval_s, "RandomCryInterval");
    getStaticParam(&mRandomCryIntervalMax_s, "RandomCryIntervalMax");
    getStaticParam(&mSpreadDist_s, "SpreadDist");
    getStaticParam(&mNoCryDist_s, "NoCryDist");
}

}  // namespace uking::ai
