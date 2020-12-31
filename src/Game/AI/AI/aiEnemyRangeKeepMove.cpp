#include "Game/AI/AI/aiEnemyRangeKeepMove.h"

namespace uking::ai {

EnemyRangeKeepMove::EnemyRangeKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRangeKeepMove::~EnemyRangeKeepMove() = default;

bool EnemyRangeKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRangeKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRangeKeepMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBackTimeMin_s, "BackTimeMin");
    getStaticParam(&mBackTimeMax_s, "BackTimeMax");
    getStaticParam(&mLeaveTimerMin_s, "LeaveTimerMin");
    getStaticParam(&mLeaveTimerMax_s, "LeaveTimerMax");
    getStaticParam(&mPosVibrateFrame_s, "PosVibrateFrame");
    getStaticParam(&mRotVelVibrateFrame_s, "RotVelVibrateFrame");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getStaticParam(&mSpaceAngle_s, "SpaceAngle");
    getStaticParam(&mNoMoveDist_s, "NoMoveDist");
    getStaticParam(&mIsCheckBack_s, "IsCheckBack");
    getStaticParam(&mIsCheckReachable_s, "IsCheckReachable");
    getAITreeVariable(&mRefPosVibrateCheckerForAI_a, "RefPosVibrateCheckerForAI");
    getAITreeVariable(&mRefVelRotVibrateCheckerforAI_a, "RefVelRotVibrateCheckerforAI");
}

}  // namespace uking::ai
