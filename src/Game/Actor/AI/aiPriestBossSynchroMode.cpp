#include "Game/Actor/AI/aiPriestBossSynchroMode.h"

namespace uking::ai {

PriestBossSynchroMode::PriestBossSynchroMode(const InitArg& arg) : PriestBoss(arg) {}

PriestBossSynchroMode::~PriestBossSynchroMode() = default;

bool PriestBossSynchroMode::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossSynchroMode::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
}

void PriestBossSynchroMode::leave_() {
    PriestBoss::leave_();
}

void PriestBossSynchroMode::loadParams_() {
    PriestBoss::loadParams_();
    getAITreeVariable(&mEquipWeaponBufIndex_a, "EquipWeaponBufIndex");
    getAITreeVariable(&mReturnFromBananaMode_a, "ReturnFromBananaMode");
}

}  // namespace uking::ai
