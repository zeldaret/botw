#include "Game/AI/AI/aiAssassinFieldShooterBattle.h"

namespace uking::ai {

AssassinFieldShooterBattle::AssassinFieldShooterBattle(const InitArg& arg)
    : AssassinFieldShooterBattleBase(arg) {}

AssassinFieldShooterBattle::~AssassinFieldShooterBattle() = default;

bool AssassinFieldShooterBattle::init_(sead::Heap* heap) {
    return AssassinFieldShooterBattleBase::init_(heap);
}

void AssassinFieldShooterBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinFieldShooterBattleBase::enter_(params);
}

void AssassinFieldShooterBattle::leave_() {
    AssassinFieldShooterBattleBase::leave_();
}

void AssassinFieldShooterBattle::loadParams_() {
    AssassinFieldShooterBattleBase::loadParams_();
}

}  // namespace uking::ai
