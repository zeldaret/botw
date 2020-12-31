#include "Game/AI/AI/aiPreSleepCheck.h"

namespace uking::ai {

PreSleepCheck::PreSleepCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreSleepCheck::~PreSleepCheck() = default;

bool PreSleepCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreSleepCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreSleepCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreSleepCheck::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mCheckRadius_s, "CheckRadius");
}

}  // namespace uking::ai
