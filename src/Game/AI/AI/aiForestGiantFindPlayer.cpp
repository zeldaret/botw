#include "Game/AI/AI/aiForestGiantFindPlayer.h"

namespace uking::ai {

ForestGiantFindPlayer::ForestGiantFindPlayer(const InitArg& arg) : LargeEnemyFindPlayer(arg) {}

ForestGiantFindPlayer::~ForestGiantFindPlayer() = default;

bool ForestGiantFindPlayer::init_(sead::Heap* heap) {
    return LargeEnemyFindPlayer::init_(heap);
}

void ForestGiantFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LargeEnemyFindPlayer::enter_(params);
}

void ForestGiantFindPlayer::leave_() {
    LargeEnemyFindPlayer::leave_();
}

void ForestGiantFindPlayer::loadParams_() {
    LargeEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai
