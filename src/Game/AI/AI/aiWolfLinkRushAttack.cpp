#include "Game/AI/AI/aiWolfLinkRushAttack.h"

namespace uking::ai {

WolfLinkRushAttack::WolfLinkRushAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkRushAttack::~WolfLinkRushAttack() = default;

bool WolfLinkRushAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkRushAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkRushAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkRushAttack::loadParams_() {
    getStaticParam(&mAttackPosOffsetLength_s, "AttackPosOffsetLength");
    getStaticParam(&mAllowUpdateTimerLength_s, "AllowUpdateTimerLength");
    getStaticParam(&mCheckSafeGround_s, "CheckSafeGround");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
