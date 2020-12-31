#include "Game/AI/AI/aiCalledEnemyMove.h"

namespace uking::ai {

CalledEnemyMove::CalledEnemyMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CalledEnemyMove::~CalledEnemyMove() = default;

bool CalledEnemyMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CalledEnemyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CalledEnemyMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CalledEnemyMove::loadParams_() {
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mWaitDist_s, "WaitDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
