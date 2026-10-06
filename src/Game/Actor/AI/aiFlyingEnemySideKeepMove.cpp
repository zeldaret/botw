#include "Game/Actor/AI/aiFlyingEnemySideKeepMove.h"

namespace uking::ai {

FlyingEnemySideKeepMove::FlyingEnemySideKeepMove(const InitArg& arg)
    : FlyingEnemyDistanceKeepMove(arg) {}

FlyingEnemySideKeepMove::~FlyingEnemySideKeepMove() = default;

bool FlyingEnemySideKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyDistanceKeepMove::init_(heap);
}

void FlyingEnemySideKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyDistanceKeepMove::enter_(params);
}

void FlyingEnemySideKeepMove::leave_() {
    FlyingEnemyDistanceKeepMove::leave_();
}

void FlyingEnemySideKeepMove::loadParams_() {
    FlyingEnemyDistanceKeepMove::loadParams_();
    getStaticParam(&mSideDirType_s, "SideDirType");
}

}  // namespace uking::ai
