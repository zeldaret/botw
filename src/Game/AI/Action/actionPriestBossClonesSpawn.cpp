#include "Game/AI/Action/actionPriestBossClonesSpawn.h"

namespace uking::action {

PriestBossClonesSpawn::PriestBossClonesSpawn(const InitArg& arg)
    : PriestBossClonesSpawnForDemo(arg) {}

PriestBossClonesSpawn::~PriestBossClonesSpawn() = default;

bool PriestBossClonesSpawn::init_(sead::Heap* heap) {
    return PriestBossClonesSpawnForDemo::init_(heap);
}

void PriestBossClonesSpawn::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossClonesSpawnForDemo::enter_(params);
}

void PriestBossClonesSpawn::leave_() {
    PriestBossClonesSpawnForDemo::leave_();
}

void PriestBossClonesSpawn::loadParams_() {
    PriestBossClonesSpawnForDemo::loadParams_();
    getStaticParam(&mASNameForAITree_s, "ASNameForAITree");
    getDynamicParam(&mDelayFrame_d, "DelayFrame");
}

void PriestBossClonesSpawn::calc_() {
    PriestBossClonesSpawnForDemo::calc_();
}

}  // namespace uking::action
