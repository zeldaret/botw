#include "Game/AI/AI/aiStalEnemySleep.h"

namespace uking::ai {

StalEnemySleep::StalEnemySleep(const InitArg& arg) : SpecialEnemySleep(arg) {}

StalEnemySleep::~StalEnemySleep() = default;

bool StalEnemySleep::init_(sead::Heap* heap) {
    return SpecialEnemySleep::init_(heap);
}

void StalEnemySleep::enter_(ksys::act::ai::InlineParamPack* params) {
    SpecialEnemySleep::enter_(params);
}

void StalEnemySleep::leave_() {
    SpecialEnemySleep::leave_();
}

void StalEnemySleep::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getStaticParam(&mUseAwarenessWakeUp_s, "UseAwarenessWakeUp");
    getStaticParam(&mUseNoticeActiveWakeUp_s, "UseNoticeActiveWakeUp");
}

}  // namespace uking::ai
