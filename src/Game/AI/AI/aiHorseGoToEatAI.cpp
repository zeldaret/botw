#include "Game/AI/AI/aiHorseGoToEatAI.h"

namespace uking::ai {

HorseGoToEatAI::HorseGoToEatAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseGoToEatAI::~HorseGoToEatAI() = default;

bool HorseGoToEatAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseGoToEatAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseGoToEatAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseGoToEatAI::loadParams_() {
    getStaticParam(&mTimeoutFrame_s, "TimeoutFrame");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
