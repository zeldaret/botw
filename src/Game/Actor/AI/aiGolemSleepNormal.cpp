#include "Game/Actor/AI/aiGolemSleepNormal.h"

namespace uking::ai {

GolemSleepNormal::GolemSleepNormal(const InitArg& arg) : SleepNormal(arg) {}

GolemSleepNormal::~GolemSleepNormal() = default;

bool GolemSleepNormal::init_(sead::Heap* heap) {
    return SleepNormal::init_(heap);
}

void GolemSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SleepNormal::enter_(params);
}

void GolemSleepNormal::leave_() {
    SleepNormal::leave_();
}

void GolemSleepNormal::loadParams_() {
    SleepNormal::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
