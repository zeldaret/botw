#include "Game/AI/AI/aiFlyingEnemyKeepMove.h"

namespace uking::ai {

FlyingEnemyKeepMove::FlyingEnemyKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FlyingEnemyKeepMove::~FlyingEnemyKeepMove() = default;

bool FlyingEnemyKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FlyingEnemyKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void FlyingEnemyKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyingEnemyKeepMove::loadParams_() {
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
