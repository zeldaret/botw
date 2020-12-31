#include "Game/AI/AI/aiPriestBossActorRoot.h"

namespace uking::ai {

PriestBossActorRoot::PriestBossActorRoot(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossActorRoot::~PriestBossActorRoot() = default;

bool PriestBossActorRoot::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossActorRoot::leave_() {
    PriestBossMode::leave_();
}

void PriestBossActorRoot::loadParams_() {
    PriestBossMode::loadParams_();
}

}  // namespace uking::ai
