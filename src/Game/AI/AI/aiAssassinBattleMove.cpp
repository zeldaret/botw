#include "Game/AI/AI/aiAssassinBattleMove.h"

namespace uking::ai {

AssassinBattleMove::AssassinBattleMove(const InitArg& arg) : EnemyRangeKeepMove(arg) {}

AssassinBattleMove::~AssassinBattleMove() = default;

bool AssassinBattleMove::init_(sead::Heap* heap) {
    return EnemyRangeKeepMove::init_(heap);
}

void AssassinBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
}

void AssassinBattleMove::leave_() {
    EnemyRangeKeepMove::leave_();
}

void AssassinBattleMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mWarpDist_s, "WarpDist");
}

}  // namespace uking::ai
