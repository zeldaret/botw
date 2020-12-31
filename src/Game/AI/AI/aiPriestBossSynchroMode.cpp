#include "Game/AI/AI/aiPriestBossSynchroMode.h"

namespace uking::ai {

PriestBossSynchroMode::PriestBossSynchroMode(const InitArg& arg) : PriestBossMode(arg) {}

PriestBossSynchroMode::~PriestBossSynchroMode() = default;

bool PriestBossSynchroMode::init_(sead::Heap* heap) {
    return PriestBossMode::init_(heap);
}

void PriestBossSynchroMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMode::enter_(params);
}

void PriestBossSynchroMode::leave_() {
    PriestBossMode::leave_();
}

void PriestBossSynchroMode::loadParams_() {
    PriestBossMode::loadParams_();
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

}  // namespace uking::ai
