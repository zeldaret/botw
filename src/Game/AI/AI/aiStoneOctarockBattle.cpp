#include "Game/AI/AI/aiStoneOctarockBattle.h"

namespace uking::ai {

StoneOctarockBattle::StoneOctarockBattle(const InitArg& arg) : ShootingEnemyBattle(arg) {}

StoneOctarockBattle::~StoneOctarockBattle() = default;

bool StoneOctarockBattle::init_(sead::Heap* heap) {
    return ShootingEnemyBattle::init_(heap);
}

void StoneOctarockBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootingEnemyBattle::enter_(params);
}

void StoneOctarockBattle::leave_() {
    ShootingEnemyBattle::leave_();
}

void StoneOctarockBattle::loadParams_() {
    ShootingEnemyBattle::loadParams_();
}

}  // namespace uking::ai
