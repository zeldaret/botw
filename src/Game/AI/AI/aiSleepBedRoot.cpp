#include "Game/AI/AI/aiSleepBedRoot.h"

namespace uking::ai {

SleepBedRoot::SleepBedRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SleepBedRoot::~SleepBedRoot() = default;

bool SleepBedRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SleepBedRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SleepBedRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SleepBedRoot::loadParams_() {}

}  // namespace uking::ai
