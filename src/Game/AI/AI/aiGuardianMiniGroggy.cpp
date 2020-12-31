#include "Game/AI/AI/aiGuardianMiniGroggy.h"

namespace uking::ai {

GuardianMiniGroggy::GuardianMiniGroggy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniGroggy::~GuardianMiniGroggy() = default;

void GuardianMiniGroggy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniGroggy::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniGroggy::loadParams_() {
    getStaticParam(&mChanceTime_s, "ChanceTime");
    getStaticParam(&mRestartASName_s, "RestartASName");
    getStaticParam(&mDefaultASName_s, "DefaultASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
