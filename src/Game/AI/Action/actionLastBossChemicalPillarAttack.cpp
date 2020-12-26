#include "Game/AI/Action/actionLastBossChemicalPillarAttack.h"

namespace uking::action {

LastBossChemicalPillarAttack::LastBossChemicalPillarAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

LastBossChemicalPillarAttack::~LastBossChemicalPillarAttack() = default;

bool LastBossChemicalPillarAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossChemicalPillarAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossChemicalPillarAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossChemicalPillarAttack::loadParams_() {
    getStaticParam(&mPillarNum_s, "PillarNum");
    getStaticParam(&mAttackEndWait_s, "AttackEndWait");
    getStaticParam(&mCreateInterval_s, "CreateInterval");
    getStaticParam(&mPillarYOffset_s, "PillarYOffset");
}

void LastBossChemicalPillarAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
