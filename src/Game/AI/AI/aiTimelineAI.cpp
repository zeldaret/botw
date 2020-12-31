#include "Game/AI/AI/aiTimelineAI.h"

namespace uking::ai {

TimelineAI::TimelineAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool TimelineAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TimelineAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TimelineAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TimelineAI::loadParams_() {
    getStaticParam(&mIntervalToCheckSchedule_s, "IntervalToCheckSchedule");
}

}  // namespace uking::ai
