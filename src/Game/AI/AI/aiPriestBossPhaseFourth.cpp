#include "Game/AI/AI/aiPriestBossPhaseFourth.h"

namespace uking::ai {

PriestBossPhaseFourth::PriestBossPhaseFourth(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseFourth::~PriestBossPhaseFourth() = default;

bool PriestBossPhaseFourth::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseFourth::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
}

void PriestBossPhaseFourth::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseFourth::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mSimAtkMax_s, "SimAtkMax");
    getStaticParam(&mBowEquipMax_s, "BowEquipMax");
    getStaticParam(&mRespawnSpan_s, "RespawnSpan");
}

}  // namespace uking::ai
