#include "Game/AI/AI/aiLynelBattle.h"

namespace uking::ai {

LynelBattle::LynelBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelBattle::~LynelBattle() = default;

bool LynelBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseBattleRepeatMax_s, "CloseBattleRepeatMax");
    getStaticParam(&mThroughAttackRepeatNum_s, "ThroughAttackRepeatNum");
    getStaticParam(&mCloseBattleStartDist_s, "CloseBattleStartDist");
    getStaticParam(&mCloseBattleStartAngle_s, "CloseBattleStartAngle");
    getStaticParam(&mHornAttackRate_s, "HornAttackRate");
    getStaticParam(&mRoarRate_s, "RoarRate");
    getStaticParam(&mBreathStartLifeRate_s, "BreathStartLifeRate");
    getStaticParam(&mRoarStartLifeRate_s, "RoarStartLifeRate");
    getStaticParam(&mBattleEndDist_s, "BattleEndDist");
    getStaticParam(&mSkipBreathRoarRate_s, "SkipBreathRoarRate");
    getStaticParam(&mRoarFlamePartsKey_s, "RoarFlamePartsKey");
    getStaticParam(&mBreathPartsKey0_s, "BreathPartsKey0");
    getStaticParam(&mBreathPartsKey1_s, "BreathPartsKey1");
    getStaticParam(&mBreathPartsKey2_s, "BreathPartsKey2");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

}  // namespace uking::ai
