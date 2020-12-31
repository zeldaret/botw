#include "Game/AI/AI/aiTargetBaitTypeSelect.h"

namespace uking::ai {

TargetBaitTypeSelect::TargetBaitTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetBaitTypeSelect::~TargetBaitTypeSelect() = default;

void TargetBaitTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetBaitTypeSelect::loadParams_() {
    getAITreeVariable(&mTargetBaitActorLink_a, "TargetBaitActorLink");
}

}  // namespace uking::ai
