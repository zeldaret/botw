#include "Game/AI/AI/aiAssassinBossFirstRangeKeepMove.h"

namespace uking::ai {

AssassinBossFirstRangeKeepMove::AssassinBossFirstRangeKeepMove(const InitArg& arg)
    : EnemyRangeKeepMove(arg) {}

AssassinBossFirstRangeKeepMove::~AssassinBossFirstRangeKeepMove() = default;

bool AssassinBossFirstRangeKeepMove::init_(sead::Heap* heap) {
    return EnemyRangeKeepMove::init_(heap);
}

void AssassinBossFirstRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
}

void AssassinBossFirstRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void AssassinBossFirstRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mNoMoveAnchorDist_s, "NoMoveAnchorDist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

}  // namespace uking::ai
