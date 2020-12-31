#include "Game/AI/AI/aiGuardianMini2ndBattle.h"

namespace uking::ai {

GuardianMini2ndBattle::GuardianMini2ndBattle(const InitArg& arg) : GuardianMiniBattle(arg) {}

GuardianMini2ndBattle::~GuardianMini2ndBattle() = default;

void GuardianMini2ndBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMiniBattle::enter_(params);
}

void GuardianMini2ndBattle::leave_() {
    GuardianMiniBattle::leave_();
}

void GuardianMini2ndBattle::loadParams_() {
    GuardianMiniBattle::loadParams_();
    getStaticParam(&mAttackHitNum_s, "AttackHitNum");
    getStaticParam(&mCounterStopTime_s, "CounterStopTime");
}

}  // namespace uking::ai
