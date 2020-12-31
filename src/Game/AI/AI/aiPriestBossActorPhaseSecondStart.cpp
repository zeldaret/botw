#include "Game/AI/AI/aiPriestBossActorPhaseSecondStart.h"

namespace uking::ai {

PriestBossActorPhaseSecondStart::PriestBossActorPhaseSecondStart(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossActorPhaseSecondStart::~PriestBossActorPhaseSecondStart() = default;

bool PriestBossActorPhaseSecondStart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossActorPhaseSecondStart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossActorPhaseSecondStart::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossActorPhaseSecondStart::loadParams_() {
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
