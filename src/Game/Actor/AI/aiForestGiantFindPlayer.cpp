#include "Game/Actor/AI/aiForestGiantFindPlayer.h"

namespace uking::ai {

ForestGiantFindPlayer::ForestGiantFindPlayer(const InitArg& arg) : GiantEnemyFindPlayer(arg) {}

ForestGiantFindPlayer::~ForestGiantFindPlayer() = default;

bool ForestGiantFindPlayer::init_(sead::Heap* heap) {
    return GiantEnemyFindPlayer::init_(heap);
}

void ForestGiantFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantEnemyFindPlayer::enter_(params);
}

void ForestGiantFindPlayer::leave_() {
    GiantEnemyFindPlayer::leave_();
}

void ForestGiantFindPlayer::loadParams_() {
    GiantEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai
