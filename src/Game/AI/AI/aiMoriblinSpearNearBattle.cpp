#include "Game/AI/AI/aiMoriblinSpearNearBattle.h"

namespace uking::ai {

MoriblinSpearNearBattle::MoriblinSpearNearBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void MoriblinSpearNearBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoriblinSpearNearBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoriblinSpearNearBattle::loadParams_() {
    getStaticParam(&mBackWalkPer_s, "BackWalkPer");
    getStaticParam(&mBackStepPer_s, "BackStepPer");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
