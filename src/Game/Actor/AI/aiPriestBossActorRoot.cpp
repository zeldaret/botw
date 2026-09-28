#include "Game/Actor/AI/aiPriestBossActorRoot.h"

namespace uking::ai {

PriestBossActorRoot::PriestBossActorRoot(const InitArg& arg) : PriestBoss(arg) {}

PriestBossActorRoot::~PriestBossActorRoot() = default;

bool PriestBossActorRoot::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossActorRoot::leave_() {
    PriestBoss::leave_();
}

void PriestBossActorRoot::loadParams_() {
    PriestBoss::loadParams_();
}

}  // namespace uking::ai
