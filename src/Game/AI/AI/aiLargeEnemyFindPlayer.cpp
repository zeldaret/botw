#include "Game/AI/AI/aiLargeEnemyFindPlayer.h"

namespace uking::ai {

LargeEnemyFindPlayer::LargeEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

LargeEnemyFindPlayer::~LargeEnemyFindPlayer() = default;

bool LargeEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void LargeEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void LargeEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void LargeEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

}  // namespace uking::ai
