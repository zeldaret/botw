#include "Game/Actor/AI/aiAssassinFieldShooterBattle.h"

namespace uking::ai {

AssassinFieldShooterBattle::AssassinFieldShooterBattle(const InitArg& arg)
    : AssassinShooterBattle(arg) {}

AssassinFieldShooterBattle::~AssassinFieldShooterBattle() = default;

bool AssassinFieldShooterBattle::init_(sead::Heap* heap) {
    return AssassinShooterBattle::init_(heap);
}

void AssassinFieldShooterBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinShooterBattle::enter_(params);
}

void AssassinFieldShooterBattle::leave_() {
    AssassinShooterBattle::leave_();
}

void AssassinFieldShooterBattle::loadParams_() {
    AssassinShooterBattle::loadParams_();
}

}  // namespace uking::ai
