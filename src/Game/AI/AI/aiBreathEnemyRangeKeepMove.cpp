#include "Game/AI/AI/aiBreathEnemyRangeKeepMove.h"

namespace uking::ai {

BreathEnemyRangeKeepMove::BreathEnemyRangeKeepMove(const InitArg& arg) : EnemyRangeKeepMove(arg) {}

BreathEnemyRangeKeepMove::~BreathEnemyRangeKeepMove() = default;

bool BreathEnemyRangeKeepMove::init_(sead::Heap* heap) {
    return EnemyRangeKeepMove::init_(heap);
}

void BreathEnemyRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
}

void BreathEnemyRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void BreathEnemyRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mBreathName_s, "BreathName");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mLoopTime_s, "LoopTime");
    getStaticParam(&mBreathEndDist_s, "BreathEndDist");
    getStaticParam(&mBreathMinTime_s, "BreathMinTime");
}

}  // namespace uking::ai
