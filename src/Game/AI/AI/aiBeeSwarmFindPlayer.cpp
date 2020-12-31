#include "Game/AI/AI/aiBeeSwarmFindPlayer.h"

namespace uking::ai {

BeeSwarmFindPlayer::BeeSwarmFindPlayer(const InitArg& arg) : FlyingEnemyFindPlayer(arg) {}

BeeSwarmFindPlayer::~BeeSwarmFindPlayer() = default;

bool BeeSwarmFindPlayer::init_(sead::Heap* heap) {
    return FlyingEnemyFindPlayer::init_(heap);
}

void BeeSwarmFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingEnemyFindPlayer::enter_(params);
}

void BeeSwarmFindPlayer::leave_() {
    FlyingEnemyFindPlayer::leave_();
}

void BeeSwarmFindPlayer::loadParams_() {
    FlyingEnemyFindPlayer::loadParams_();
}

}  // namespace uking::ai
