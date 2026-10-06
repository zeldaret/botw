#include "Game/Actor/AI/aiSleepNormal.h"

namespace uking::ai {

SleepNormal::SleepNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SleepNormal::~SleepNormal() = default;

bool SleepNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SleepNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SleepNormal::loadParams_() {
    getStaticParam(&mAwakeDelayTime_s, "AwakeDelayTime");
    getStaticParam(&mIsAwakenByHearing_s, "IsAwakenByHearing");
    getStaticParam(&mIsWaitAfterAwaken_s, "IsWaitAfterAwaken");
}

}  // namespace uking::ai
