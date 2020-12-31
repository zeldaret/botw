#include "Game/AI/AI/aiGuardFlagSelect.h"

namespace uking::ai {

GuardFlagSelect::GuardFlagSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardFlagSelect::~GuardFlagSelect() = default;

void GuardFlagSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardFlagSelect::loadParams_() {}

}  // namespace uking::ai
