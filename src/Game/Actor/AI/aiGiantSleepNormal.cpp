#include "Game/Actor/AI/aiGiantSleepNormal.h"

namespace uking::ai {

GiantSleepNormal::GiantSleepNormal(const InitArg& arg) : SleepNormal(arg) {}

GiantSleepNormal::~GiantSleepNormal() = default;

bool GiantSleepNormal::init_(sead::Heap* heap) {
    return SleepNormal::init_(heap);
}

void GiantSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SleepNormal::enter_(params);
}

void GiantSleepNormal::leave_() {
    SleepNormal::leave_();
}

void GiantSleepNormal::loadParams_() {
    SleepNormal::loadParams_();
    getStaticParam(&mForceAwakeDist_s, "ForceAwakeDist");
    getStaticParam(&mAwakeRbName_s, "AwakeRbName");
}

}  // namespace uking::ai
