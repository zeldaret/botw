#include "Game/AI/AI/aiSpecialEnemySleep.h"

namespace uking::ai {

SpecialEnemySleep::SpecialEnemySleep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SpecialEnemySleep::~SpecialEnemySleep() = default;

bool SpecialEnemySleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SpecialEnemySleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SpecialEnemySleep::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SpecialEnemySleep::loadParams_() {
    getStaticParam(&mAwakeDelayTime_s, "AwakeDelayTime");
    getStaticParam(&mIsAwakenByHearing_s, "IsAwakenByHearing");
    getStaticParam(&mIsWaitAfterAwaken_s, "IsWaitAfterAwaken");
}

}  // namespace uking::ai
