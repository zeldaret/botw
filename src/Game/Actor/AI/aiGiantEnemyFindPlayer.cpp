#include "Game/Actor/AI/aiGiantEnemyFindPlayer.h"

namespace uking::ai {

GiantEnemyFindPlayer::GiantEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

GiantEnemyFindPlayer::~GiantEnemyFindPlayer() = default;

bool GiantEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void GiantEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void GiantEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void GiantEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
}

}  // namespace uking::ai
