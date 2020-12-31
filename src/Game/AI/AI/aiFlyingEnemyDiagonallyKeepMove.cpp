#include "Game/AI/AI/aiFlyingEnemyDiagonallyKeepMove.h"

namespace uking::ai {

FlyingEnemyDiagonallyKeepMove::FlyingEnemyDiagonallyKeepMove(const InitArg& arg)
    : FlyingEnemySideKeepMove(arg) {}

FlyingEnemyDiagonallyKeepMove::~FlyingEnemyDiagonallyKeepMove() = default;

void FlyingEnemyDiagonallyKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemySideKeepMove::enter_(params);
}

void FlyingEnemyDiagonallyKeepMove::leave_() {
    FlyingEnemySideKeepMove::leave_();
}

void FlyingEnemyDiagonallyKeepMove::loadParams_() {
    FlyingEnemySideKeepMove::loadParams_();
    getStaticParam(&mDiagAngle_s, "DiagAngle");
}

}  // namespace uking::ai
