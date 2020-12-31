#include "Game/AI/AI/aiGuardianMini2ndBattleAttack.h"

namespace uking::ai {

GuardianMini2ndBattleAttack::GuardianMini2ndBattleAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMini2ndBattleAttack::~GuardianMini2ndBattleAttack() = default;

bool GuardianMini2ndBattleAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianMini2ndBattleAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMini2ndBattleAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMini2ndBattleAttack::loadParams_() {
    getStaticParam(&mAscendingCurrentName_s, "AscendingCurrentName");
    getStaticParam(&mAscendingCurrentTime_s, "AscendingCurrentTime");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

}  // namespace uking::ai
