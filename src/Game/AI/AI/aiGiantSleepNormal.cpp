#include "Game/AI/AI/aiGiantSleepNormal.h"

namespace uking::ai {

GiantSleepNormal::GiantSleepNormal(const InitArg& arg) : SpecialEnemySleep(arg) {}

GiantSleepNormal::~GiantSleepNormal() = default;

bool GiantSleepNormal::init_(sead::Heap* heap) {
    return SpecialEnemySleep::init_(heap);
}

void GiantSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SpecialEnemySleep::enter_(params);
}

void GiantSleepNormal::leave_() {
    SpecialEnemySleep::leave_();
}

void GiantSleepNormal::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getStaticParam(&mForceAwakeDist_s, "ForceAwakeDist");
    getStaticParam(&mAwakeRbName_s, "AwakeRbName");
}

}  // namespace uking::ai
