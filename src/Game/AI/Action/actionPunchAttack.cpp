#include "Game/AI/Action/actionPunchAttack.h"

namespace uking::action {

PunchAttack::PunchAttack(const InitArg& arg) : ActionWithAS(arg) {}

PunchAttack::~PunchAttack() = default;

bool PunchAttack::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void PunchAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void PunchAttack::leave_() {
    ActionWithAS::leave_();
}

void PunchAttack::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    getStaticParam(&mIsHeavy_s, "IsHeavy");
    getStaticParam(&mIsHammer_s, "IsHammer");
    getStaticParam(&mASName_s, "ASName");
    // FIXME: CALL _ZN4sead17StringBuilderBaseIcE6formatEPKcz @ 0x7100b0d550
    // FIXME: CALL _ZN4sead17StringBuilderBaseIcE6formatEPKcz @ 0x7100b0d550
    // FIXME: CALL _ZN4sead17StringBuilderBaseIcE6formatEPKcz @ 0x7100b0d550
}

void PunchAttack::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
