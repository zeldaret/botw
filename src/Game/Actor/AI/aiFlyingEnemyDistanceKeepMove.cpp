#include "Game/Actor/AI/aiFlyingEnemyDistanceKeepMove.h"

namespace uking::ai {

FlyingEnemyDistanceKeepMove::FlyingEnemyDistanceKeepMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

FlyingEnemyDistanceKeepMove::~FlyingEnemyDistanceKeepMove() = default;

bool FlyingEnemyDistanceKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FlyingEnemyDistanceKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FlyingEnemyDistanceKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyingEnemyDistanceKeepMove::loadParams_() {
    getStaticParam(&mLostDistance_s, "LostDistance");
    getStaticParam(&mAngleRange_s, "AngleRange");
    getStaticParam(&mSpaceDistance_s, "SpaceDistance");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mBaseHeight_s, "BaseHeight");
    getStaticParam(&mLowHeight_s, "LowHeight");
    getStaticParam(&mHighHeight_s, "HighHeight");
}

}  // namespace uking::ai
