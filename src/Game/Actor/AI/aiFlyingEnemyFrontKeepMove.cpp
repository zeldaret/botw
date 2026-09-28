#include "Game/Actor/AI/aiFlyingEnemyFrontKeepMove.h"

namespace uking::ai {

FlyingEnemyFrontKeepMove::FlyingEnemyFrontKeepMove(const InitArg& arg)
    : FlyingEnemyDistanceKeepMove(arg) {}

FlyingEnemyFrontKeepMove::~FlyingEnemyFrontKeepMove() = default;

bool FlyingEnemyFrontKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyDistanceKeepMove::init_(heap);
}

void FlyingEnemyFrontKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyDistanceKeepMove::enter_(params);
}

void FlyingEnemyFrontKeepMove::leave_() {
    FlyingEnemyDistanceKeepMove::leave_();
}

void FlyingEnemyFrontKeepMove::loadParams_() {
    FlyingEnemyDistanceKeepMove::loadParams_();
}

}  // namespace uking::ai
