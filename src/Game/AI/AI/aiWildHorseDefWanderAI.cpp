#include "Game/AI/AI/aiWildHorseDefWanderAI.h"

namespace uking::ai {

WildHorseDefWanderAI::WildHorseDefWanderAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WildHorseDefWanderAI::~WildHorseDefWanderAI() = default;

bool WildHorseDefWanderAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WildHorseDefWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WildHorseDefWanderAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WildHorseDefWanderAI::loadParams_() {
    getStaticParam(&mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mMaxWaitTime_s, "MaxWaitTime");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
}

}  // namespace uking::ai
