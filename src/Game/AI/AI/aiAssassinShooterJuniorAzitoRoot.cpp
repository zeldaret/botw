#include "Game/AI/AI/aiAssassinShooterJuniorAzitoRoot.h"

namespace uking::ai {

AssassinShooterJuniorAzitoRoot::AssassinShooterJuniorAzitoRoot(const InitArg& arg)
    : RememberMesOneActorEnemyRoot(arg) {}

AssassinShooterJuniorAzitoRoot::~AssassinShooterJuniorAzitoRoot() = default;

bool AssassinShooterJuniorAzitoRoot::init_(sead::Heap* heap) {
    return RememberMesOneActorEnemyRoot::init_(heap);
}

void AssassinShooterJuniorAzitoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RememberMesOneActorEnemyRoot::enter_(params);
}

void AssassinShooterJuniorAzitoRoot::leave_() {
    RememberMesOneActorEnemyRoot::leave_();
}

void AssassinShooterJuniorAzitoRoot::loadParams_() {
    RememberMesOneActorEnemyRoot::loadParams_();
}

}  // namespace uking::ai
