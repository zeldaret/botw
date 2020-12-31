#include "Game/AI/AI/aiFlyingEnemySideKeepMove.h"

namespace uking::ai {

FlyingEnemySideKeepMove::FlyingEnemySideKeepMove(const InitArg& arg) : FlyingEnemyKeepMove(arg) {}

FlyingEnemySideKeepMove::~FlyingEnemySideKeepMove() = default;

bool FlyingEnemySideKeepMove::init_(sead::Heap* heap) {
    return FlyingEnemyKeepMove::init_(heap);
}

void FlyingEnemySideKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyKeepMove::enter_(params);
}

void FlyingEnemySideKeepMove::leave_() {
    FlyingEnemyKeepMove::leave_();
}

void FlyingEnemySideKeepMove::loadParams_() {
    FlyingEnemyKeepMove::loadParams_();
    getStaticParam(&mSideDirType_s, "SideDirType");
}

}  // namespace uking::ai
