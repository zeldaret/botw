#include "Game/AI/AI/aiGolemFireREnemyBattle.h"

namespace uking::ai {

GolemFireREnemyBattle::GolemFireREnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

GolemFireREnemyBattle::~GolemFireREnemyBattle() = default;

bool GolemFireREnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void GolemFireREnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void GolemFireREnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void GolemFireREnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mPlayerRecoverFromFallFrames_s, "PlayerRecoverFromFallFrames");
}

}  // namespace uking::ai
