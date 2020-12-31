#include "Game/AI/AI/aiPreyDefWanderAI.h"

namespace uking::ai {

PreyDefWanderAI::PreyDefWanderAI(const InitArg& arg) : DefWanderAI(arg) {}

PreyDefWanderAI::~PreyDefWanderAI() = default;

bool PreyDefWanderAI::init_(sead::Heap* heap) {
    return DefWanderAI::init_(heap);
}

void PreyDefWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    DefWanderAI::enter_(params);
}

void PreyDefWanderAI::leave_() {
    DefWanderAI::leave_();
}

void PreyDefWanderAI::loadParams_() {
    DefWanderAI::loadParams_();
    getStaticParam(&mTimesStuckLimit_s, "TimesStuckLimit");
    getStaticParam(&mFramesStuckLimit_s, "FramesStuckLimit");
    getAITreeVariable(&mFramesStuckOnTerrain_a, "FramesStuckOnTerrain");
    getAITreeVariable(&mIsStuckOnTerrain_a, "IsStuckOnTerrain");
}

}  // namespace uking::ai
