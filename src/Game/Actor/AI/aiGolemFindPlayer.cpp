#include "Game/Actor/AI/aiGolemFindPlayer.h"

namespace uking::ai {

GolemFindPlayer::GolemFindPlayer(const InitArg& arg) : GiantEnemyFindPlayer(arg) {}

GolemFindPlayer::~GolemFindPlayer() = default;

bool GolemFindPlayer::init_(sead::Heap* heap) {
    return GiantEnemyFindPlayer::init_(heap);
}

void GolemFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantEnemyFindPlayer::enter_(params);
}

void GolemFindPlayer::leave_() {
    GiantEnemyFindPlayer::leave_();
}

void GolemFindPlayer::loadParams_() {
    GiantEnemyFindPlayer::loadParams_();
    getStaticParam(&mSearchExplosiveDist_s, "SearchExplosiveDist");
}

}  // namespace uking::ai
