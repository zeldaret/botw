#include "Game/AI/AI/aiMoriblinSpearBattle.h"

namespace uking::ai {

MoriblinSpearBattle::MoriblinSpearBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoriblinSpearBattle::~MoriblinSpearBattle() = default;

void MoriblinSpearBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoriblinSpearBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoriblinSpearBattle::loadParams_() {
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mAttackStartRotate_s, "AttackStartRotate");
    getStaticParam(&mForceAttackDist_s, "ForceAttackDist");
}

}  // namespace uking::ai
