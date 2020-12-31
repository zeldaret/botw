#include "Game/AI/AI/aiHiddenOctarockNormal.h"

namespace uking::ai {

HiddenOctarockNormal::HiddenOctarockNormal(const InitArg& arg) : EnemyNormal(arg) {}

HiddenOctarockNormal::~HiddenOctarockNormal() = default;

bool HiddenOctarockNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void HiddenOctarockNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void HiddenOctarockNormal::leave_() {
    EnemyNormal::leave_();
}

void HiddenOctarockNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mOptionHitReactionDelay_s, "OptionHitReactionDelay");
    getStaticParam(&mIsSitDown_s, "IsSitDown");
    getStaticParam(&mIsHitGround_s, "IsHitGround");
    getStaticParam(&mIsReactionByWigHit_s, "IsReactionByWigHit");
    getStaticParam(&mIsHide_s, "IsHide");
    getStaticParam(&mIsIvalidateSight_s, "IsIvalidateSight");
    getStaticParam(&mIsSealHearing_s, "IsSealHearing");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
}

}  // namespace uking::ai
