#include "Game/AI/Action/actionGanonWeaponNearAttack.h"

namespace uking::action {

GanonWeaponNearAttack::GanonWeaponNearAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonWeaponNearAttack::~GanonWeaponNearAttack() = default;

bool GanonWeaponNearAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonWeaponNearAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonWeaponNearAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonWeaponNearAttack::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtkMinPower_s, "AtkMinPower");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mAttackCancelDist_s, "AttackCancelDist");
    getStaticParam(&mAttackCancelAng_s, "AttackCancelAng");
    getStaticParam(&mBattleNodeOffsetLR_s, "BattleNodeOffsetLR");
    getStaticParam(&mBattleNodeOffsetUD_s, "BattleNodeOffsetUD");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsGuardBreak_s, "IsGuardBreak");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonWeaponNearAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
