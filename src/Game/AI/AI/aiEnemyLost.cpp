#include "Game/AI/AI/aiEnemyLost.h"

namespace uking::ai {

EnemyLost::EnemyLost(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyLost::~EnemyLost() = default;

bool EnemyLost::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyLost::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyLost::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyLost::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mRailCheckInterval_s, "RailCheckInterval");
    getStaticParam(&mSealForceReturn_s, "SealForceReturn");
    getStaticParam(&mForceReturnNoCameraRad_s, "ForceReturnNoCameraRad");
}

}  // namespace uking::ai
