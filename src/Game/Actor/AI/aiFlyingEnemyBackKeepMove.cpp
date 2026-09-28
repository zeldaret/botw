#include "Game/Actor/AI/aiFlyingEnemyBackKeepMove.h"

namespace uking::ai {

FlyingEnemyBackKeepMove::FlyingEnemyBackKeepMove(const InitArg& arg)
    : FlyingEnemyDistanceKeepMove(arg) {}

FlyingEnemyBackKeepMove::~FlyingEnemyBackKeepMove() = default;

bool FlyingEnemyBackKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyDistanceKeepMove::init_(heap);
}

void FlyingEnemyBackKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyDistanceKeepMove::enter_(params);
}

void FlyingEnemyBackKeepMove::leave_() {
    FlyingEnemyDistanceKeepMove::leave_();
}

void FlyingEnemyBackKeepMove::loadParams_() {
    FlyingEnemyDistanceKeepMove::loadParams_();
}

}  // namespace uking::ai
