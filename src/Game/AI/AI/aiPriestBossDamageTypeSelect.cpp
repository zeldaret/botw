#include "Game/AI/AI/aiPriestBossDamageTypeSelect.h"

namespace uking::ai {

PriestBossDamageTypeSelect::PriestBossDamageTypeSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossDamageTypeSelect::~PriestBossDamageTypeSelect() = default;

bool PriestBossDamageTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossDamageTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossDamageTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossDamageTypeSelect::loadParams_() {}

}  // namespace uking::ai
