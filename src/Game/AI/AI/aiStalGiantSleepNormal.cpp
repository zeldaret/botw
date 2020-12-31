#include "Game/AI/AI/aiStalGiantSleepNormal.h"

namespace uking::ai {

StalGiantSleepNormal::StalGiantSleepNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalGiantSleepNormal::~StalGiantSleepNormal() = default;

bool StalGiantSleepNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalGiantSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalGiantSleepNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalGiantSleepNormal::loadParams_() {
    getStaticParam(&mAwakeDelayTime_s, "AwakeDelayTime");
    getStaticParam(&mIsAwakenByHearing_s, "IsAwakenByHearing");
    getStaticParam(&mIsWaitAfterAwaken_s, "IsWaitAfterAwaken");
}

}  // namespace uking::ai
