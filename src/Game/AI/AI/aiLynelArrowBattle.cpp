#include "Game/AI/AI/aiLynelArrowBattle.h"

namespace uking::ai {

LynelArrowBattle::LynelArrowBattle(const InitArg& arg) : EnemyBattle(arg) {}

LynelArrowBattle::~LynelArrowBattle() = default;

bool LynelArrowBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void LynelArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void LynelArrowBattle::leave_() {
    EnemyBattle::leave_();
}

void LynelArrowBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackCount_s, "AttackCount");
    getStaticParam(&mFrontCheckBoneName_s, "FrontCheckBoneName");
    getStaticParam(&mFrontDirFromBone_s, "FrontDirFromBone");
}

}  // namespace uking::ai
