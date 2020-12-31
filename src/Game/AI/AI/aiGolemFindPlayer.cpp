#include "Game/AI/AI/aiGolemFindPlayer.h"

namespace uking::ai {

GolemFindPlayer::GolemFindPlayer(const InitArg& arg) : LargeEnemyFindPlayer(arg) {}

GolemFindPlayer::~GolemFindPlayer() = default;

bool GolemFindPlayer::init_(sead::Heap* heap) {
    return LargeEnemyFindPlayer::init_(heap);
}

void GolemFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    LargeEnemyFindPlayer::enter_(params);
}

void GolemFindPlayer::leave_() {
    LargeEnemyFindPlayer::leave_();
}

void GolemFindPlayer::loadParams_() {
    LargeEnemyFindPlayer::loadParams_();
    getStaticParam(&mSearchExplosiveDist_s, "SearchExplosiveDist");
}

}  // namespace uking::ai
