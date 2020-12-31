#include "Game/AI/AI/aiBokoblinArrowAttack.h"

namespace uking::ai {

BokoblinArrowAttack::BokoblinArrowAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void BokoblinArrowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BokoblinArrowAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBackWalkStartDist_s, "BackWalkStartDist");
    getStaticParam(&mBackWalkEndDist_s, "BackWalkEndDist");
    getStaticParam(&mCliffCheckDist_s, "CliffCheckDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
