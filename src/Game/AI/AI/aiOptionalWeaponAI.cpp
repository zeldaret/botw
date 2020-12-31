#include "Game/AI/AI/aiOptionalWeaponAI.h"

namespace uking::ai {

OptionalWeaponAI::OptionalWeaponAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void OptionalWeaponAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OptionalWeaponAI::loadParams_() {}

}  // namespace uking::ai
