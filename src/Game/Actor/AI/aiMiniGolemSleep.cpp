#include "Game/Actor/AI/aiMiniGolemSleep.h"

namespace uking::ai {

MiniGolemSleep::MiniGolemSleep(const InitArg& arg) : SleepNormal(arg) {}

MiniGolemSleep::~MiniGolemSleep() = default;

bool MiniGolemSleep::init_(sead::Heap* heap) {
    return SleepNormal::init_(heap);
}

void MiniGolemSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    SleepNormal::enter_(params);
}

void MiniGolemSleep::leave_() {
    SleepNormal::leave_();
}

void MiniGolemSleep::loadParams_() {
    SleepNormal::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
