#include "Game/AI/AI/aiAssassinBattleRange.h"

namespace uking::ai {

AssassinBattleRange::AssassinBattleRange(const InitArg& arg) : EnemyBattle(arg) {}

AssassinBattleRange::~AssassinBattleRange() = default;

bool AssassinBattleRange::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void AssassinBattleRange::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void AssassinBattleRange::leave_() {
    EnemyBattle::leave_();
}

void AssassinBattleRange::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mScapeGoatCheckInterval_s, "ScapeGoatCheckInterval");
    getStaticParam(&mServiceCheckInterval_s, "ServiceCheckInterval");
    getStaticParam(&mServicePer_s, "ServicePer");
    getStaticParam(&mScapeGoatPer_s, "ScapeGoatPer");
    getStaticParam(&mServiceDist_s, "ServiceDist");
}

}  // namespace uking::ai
