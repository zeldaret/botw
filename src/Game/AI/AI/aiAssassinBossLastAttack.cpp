#include "Game/AI/AI/aiAssassinBossLastAttack.h"

namespace uking::ai {

AssassinBossLastAttack::AssassinBossLastAttack(const InitArg& arg)
    : AssassinBossIronBallAttack(arg) {}

AssassinBossLastAttack::~AssassinBossLastAttack() = default;

bool AssassinBossLastAttack::init_(sead::Heap* heap) {
    return AssassinBossIronBallAttack::init_(heap);
}

void AssassinBossLastAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinBossIronBallAttack::enter_(params);
}

void AssassinBossLastAttack::leave_() {
    AssassinBossIronBallAttack::leave_();
}

void AssassinBossLastAttack::loadParams_() {
    AssassinBossIronBallAttack::loadParams_();
}

}  // namespace uking::ai
