#include "Game/AI/AI/aiFlyingEnemyBackKeepMove.h"

namespace uking::ai {

FlyingEnemyBackKeepMove::FlyingEnemyBackKeepMove(const InitArg& arg) : FlyingEnemyKeepMove(arg) {}

FlyingEnemyBackKeepMove::~FlyingEnemyBackKeepMove() = default;

bool FlyingEnemyBackKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyKeepMove::init_(heap);
}

void FlyingEnemyBackKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyKeepMove::enter_(params);
}

void FlyingEnemyBackKeepMove::leave_() {
    FlyingEnemyKeepMove::leave_();
}

void FlyingEnemyBackKeepMove::loadParams_() {
    FlyingEnemyKeepMove::loadParams_();
}

}  // namespace uking::ai
