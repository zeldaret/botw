#include "Game/AI/AI/aiAnimalTimelineAI.h"

namespace uking::ai {

AnimalTimelineAI::AnimalTimelineAI(const InitArg& arg) : TimelineAI(arg) {}

AnimalTimelineAI::~AnimalTimelineAI() = default;

bool AnimalTimelineAI::init_(sead::Heap* heap) {
    return TimelineAI::init_(heap);
}

void AnimalTimelineAI::enter_(ksys::act::ai::InlineParamPack* params) {
    TimelineAI::enter_(params);
}

void AnimalTimelineAI::leave_() {
    TimelineAI::leave_();
}

void AnimalTimelineAI::loadParams_() {
    TimelineAI::loadParams_();
    getAITreeVariable(&mDomesticAnimalRailName_a, "DomesticAnimalRailName");
}

}  // namespace uking::ai
