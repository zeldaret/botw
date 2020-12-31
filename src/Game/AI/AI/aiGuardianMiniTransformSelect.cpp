#include "Game/AI/AI/aiGuardianMiniTransformSelect.h"

namespace uking::ai {

GuardianMiniTransformSelect::GuardianMiniTransformSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniTransformSelect::~GuardianMiniTransformSelect() = default;

void GuardianMiniTransformSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniTransformSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniTransformSelect::loadParams_() {
    getAITreeVariable(&mIsTransformedGuardianMini_a, "IsTransformedGuardianMini");
}

}  // namespace uking::ai
