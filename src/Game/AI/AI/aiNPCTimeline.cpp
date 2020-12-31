#include "Game/AI/AI/aiNPCTimeline.h"

namespace uking::ai {

NPCTimeline::NPCTimeline(const InitArg& arg) : TimelineAI(arg) {}

NPCTimeline::~NPCTimeline() = default;

bool NPCTimeline::init_(sead::Heap* heap) {
    return TimelineAI::init_(heap);
}

void NPCTimeline::enter_(ksys::act::ai::InlineParamPack* params) {
    TimelineAI::enter_(params);
}

void NPCTimeline::leave_() {
    TimelineAI::leave_();
}

void NPCTimeline::loadParams_() {
    TimelineAI::loadParams_();
}

}  // namespace uking::ai
