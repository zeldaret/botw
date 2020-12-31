#include "Game/AI/AI/aiLastBossShootNormalArrowRoot.h"

namespace uking::ai {

LastBossShootNormalArrowRoot::LastBossShootNormalArrowRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LastBossShootNormalArrowRoot::~LastBossShootNormalArrowRoot() = default;

bool LastBossShootNormalArrowRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossShootNormalArrowRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossShootNormalArrowRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossShootNormalArrowRoot::loadParams_() {
    getStaticParam(&mArrowNum_s, "ArrowNum");
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mBattleNodeOffsetLR_s, "BattleNodeOffsetLR");
    getStaticParam(&mBattleNodeOffsetUD_s, "BattleNodeOffsetUD");
    getStaticParam(&mIsPrepreNextArrow_s, "IsPrepreNextArrow");
    getStaticParam(&mArrowName_s, "ArrowName");
    getStaticParam(&mPartsName_s, "PartsName");
    getStaticParam(&mReflectOffset_s, "ReflectOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
