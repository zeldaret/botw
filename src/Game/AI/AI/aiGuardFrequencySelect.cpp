#include "Game/AI/AI/aiGuardFrequencySelect.h"

namespace uking::ai {

GuardFrequencySelect::GuardFrequencySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardFrequencySelect::~GuardFrequencySelect() = default;

void GuardFrequencySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardFrequencySelect::loadParams_() {}

}  // namespace uking::ai
