#include "Game/AI/AI/aiFlyingEnemyFindPlayer.h"

namespace uking::ai {

FlyingEnemyFindPlayer::FlyingEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

FlyingEnemyFindPlayer::~FlyingEnemyFindPlayer() = default;

bool FlyingEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void FlyingEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void FlyingEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void FlyingEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

}  // namespace uking::ai
