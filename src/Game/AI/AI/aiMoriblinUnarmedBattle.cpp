#include "Game/AI/AI/aiMoriblinUnarmedBattle.h"

namespace uking::ai {

MoriblinUnarmedBattle::MoriblinUnarmedBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoriblinUnarmedBattle::~MoriblinUnarmedBattle() = default;

void MoriblinUnarmedBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoriblinUnarmedBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoriblinUnarmedBattle::loadParams_() {
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mAttackStartRotate_s, "AttackStartRotate");
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

}  // namespace uking::ai
