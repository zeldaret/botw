#include "Game/AI/Action/actionLastBossThunderAppear.h"

namespace uking::action {

LastBossThunderAppear::LastBossThunderAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossThunderAppear::~LastBossThunderAppear() = default;

bool LastBossThunderAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossThunderAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossThunderAppear::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossThunderAppear::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAppearTime_s, "AppearTime");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
}

void LastBossThunderAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
