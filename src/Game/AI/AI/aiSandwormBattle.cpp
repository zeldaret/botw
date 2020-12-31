#include "Game/AI/AI/aiSandwormBattle.h"

namespace uking::ai {

SandwormBattle::SandwormBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormBattle::~SandwormBattle() = default;

bool SandwormBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormBattle::loadParams_() {
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mAttackInterval_s, "AttackInterval");
    getStaticParam(&mAttackIntervalRand_s, "AttackIntervalRand");
    getStaticParam(&mBattleFailTimer_s, "BattleFailTimer");
}

}  // namespace uking::ai
