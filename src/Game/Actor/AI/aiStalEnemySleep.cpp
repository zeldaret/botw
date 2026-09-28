#include "Game/Actor/AI/aiStalEnemySleep.h"

namespace uking::ai {

StalEnemySleep::StalEnemySleep(const InitArg& arg) : SleepNormal(arg) {}

StalEnemySleep::~StalEnemySleep() = default;

bool StalEnemySleep::init_(sead::Heap* heap) {
    return SleepNormal::init_(heap);
}

void StalEnemySleep::enter_(ksys::act::ai::InlineParamPack* params) {
    SleepNormal::enter_(params);
}

void StalEnemySleep::leave_() {
    SleepNormal::leave_();
}

void StalEnemySleep::loadParams_() {
    SleepNormal::loadParams_();
    getStaticParam(&mUseAwarenessWakeUp_s, "UseAwarenessWakeUp");
    getStaticParam(&mUseNoticeActiveWakeUp_s, "UseNoticeActiveWakeUp");
}

}  // namespace uking::ai
