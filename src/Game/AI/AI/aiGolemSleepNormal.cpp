#include "Game/AI/AI/aiGolemSleepNormal.h"

namespace uking::ai {

GolemSleepNormal::GolemSleepNormal(const InitArg& arg) : SpecialEnemySleep(arg) {}

GolemSleepNormal::~GolemSleepNormal() = default;

bool GolemSleepNormal::init_(sead::Heap* heap) {
    return SpecialEnemySleep::init_(heap);
}

void GolemSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SpecialEnemySleep::enter_(params);
}

void GolemSleepNormal::leave_() {
    SpecialEnemySleep::leave_();
}

void GolemSleepNormal::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
