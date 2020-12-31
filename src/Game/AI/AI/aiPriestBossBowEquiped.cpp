#include "Game/AI/AI/aiPriestBossBowEquiped.h"

namespace uking::ai {

PriestBossBowEquiped::PriestBossBowEquiped(const InitArg& arg) : BowEquiped(arg) {}

PriestBossBowEquiped::~PriestBossBowEquiped() = default;

bool PriestBossBowEquiped::init_(sead::Heap* heap) {
    return BowEquiped::init_(heap);
}

void PriestBossBowEquiped::enter_(ksys::act::ai::InlineParamPack* params) {
    BowEquiped::enter_(params);
}

void PriestBossBowEquiped::leave_() {
    BowEquiped::leave_();
}

void PriestBossBowEquiped::loadParams_() {}

}  // namespace uking::ai
