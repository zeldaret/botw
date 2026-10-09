#include "Game/Actor/Action/actionDynamicAttackPowerExplode.h"

namespace uking::action {

DynamicAttackPowerExplode::DynamicAttackPowerExplode(const InitArg& arg) : EitherSideExplode(arg) {}

DynamicAttackPowerExplode::~DynamicAttackPowerExplode() = default;

bool DynamicAttackPowerExplode::init_(sead::Heap* heap) {
    return EitherSideExplode::init_(heap);
}

void DynamicAttackPowerExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    EitherSideExplode::enter_(params);
}

void DynamicAttackPowerExplode::leave_() {
    EitherSideExplode::leave_();
}

void DynamicAttackPowerExplode::loadParams_() {
    EitherSideExplode::loadParams_();
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mMinDamage_s, "MinDamage");
    getStaticParam(&mPlayerDamage_s, "PlayerDamage");
}

void DynamicAttackPowerExplode::calc_() {
    EitherSideExplode::calc_();
}

}  // namespace uking::action
