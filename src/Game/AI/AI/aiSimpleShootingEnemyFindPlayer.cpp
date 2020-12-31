#include "Game/AI/AI/aiSimpleShootingEnemyFindPlayer.h"

namespace uking::ai {

SimpleShootingEnemyFindPlayer::SimpleShootingEnemyFindPlayer(const InitArg& arg)
    : EnemyBaseFindPlayer(arg) {}

SimpleShootingEnemyFindPlayer::~SimpleShootingEnemyFindPlayer() = default;

bool SimpleShootingEnemyFindPlayer::init_(sead::Heap* heap) {
    return EnemyBaseFindPlayer::init_(heap);
}

void SimpleShootingEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void SimpleShootingEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void SimpleShootingEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mShootBaseDist_s, "ShootBaseDist");
    getStaticParam(&mShootDistRatio_s, "ShootDistRatio");
}

}  // namespace uking::ai
