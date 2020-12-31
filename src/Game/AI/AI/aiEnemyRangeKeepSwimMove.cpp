#include "Game/AI/AI/aiEnemyRangeKeepSwimMove.h"

namespace uking::ai {

EnemyRangeKeepSwimMove::EnemyRangeKeepSwimMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRangeKeepSwimMove::~EnemyRangeKeepSwimMove() = default;

bool EnemyRangeKeepSwimMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRangeKeepSwimMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRangeKeepSwimMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRangeKeepSwimMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
}

}  // namespace uking::ai
