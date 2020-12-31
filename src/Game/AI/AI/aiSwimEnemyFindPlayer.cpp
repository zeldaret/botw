#include "Game/AI/AI/aiSwimEnemyFindPlayer.h"

namespace uking::ai {

SwimEnemyFindPlayer::SwimEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

SwimEnemyFindPlayer::~SwimEnemyFindPlayer() = default;

bool SwimEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void SwimEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void SwimEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void SwimEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mIsAbleToLand_s, "IsAbleToLand");
    getStaticParam(&mNearScaffoldDist_s, "NearScaffoldDist");
    getStaticParam(&mClimbVmin_s, "ClimbVmin");
    getStaticParam(&mClimbVmax_s, "ClimbVmax");
    getStaticParam(&mClimbHmax_s, "ClimbHmax");
}

}  // namespace uking::ai
