#include "Game/AI/AI/aiLynelCloseBattle.h"

namespace uking::ai {

LynelCloseBattle::LynelCloseBattle(const InitArg& arg) : EnemyBattle(arg) {}

LynelCloseBattle::~LynelCloseBattle() = default;

bool LynelCloseBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void LynelCloseBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void LynelCloseBattle::leave_() {
    EnemyBattle::leave_();
}

void LynelCloseBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mBackAngleAction_s, "BackAngleAction");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

}  // namespace uking::ai
