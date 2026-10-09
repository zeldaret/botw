#include "Game/Actor/Action/actionAttackWithAS.h"

namespace uking::action {

AttackWithAS::AttackWithAS(const InitArg& arg) : TurnGiantAttack(arg) {}

AttackWithAS::~AttackWithAS() = default;

bool AttackWithAS::init_(sead::Heap* heap) {
    return TurnGiantAttack::init_(heap);
}

void AttackWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnGiantAttack::enter_(params);
}

void AttackWithAS::leave_() {
    TurnGiantAttack::leave_();
}

void AttackWithAS::loadParams_() {
    TurnGiantAttack::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void AttackWithAS::calc_() {
    TurnGiantAttack::calc_();
}

}  // namespace uking::action
