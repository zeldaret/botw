#include "Game/AI/Action/actionPriestBossBeamMove.h"

namespace uking::action {

PriestBossBeamMove::PriestBossBeamMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossBeamMove::~PriestBossBeamMove() = default;

bool PriestBossBeamMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossBeamMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossBeamMove::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mShieldDamage_s, "ShieldDamage");
    getStaticParam(&mContactWaitFrame_s, "ContactWaitFrame");
    getStaticParam(&mReflectDeccel_s, "ReflectDeccel");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mPosOffset_m, "PosOffset");
}

void PriestBossBeamMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
