#include "Game/AI/AI/aiEventTagRootAI.h"

namespace uking::ai {

EventTagRootAI::EventTagRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EventTagRootAI::~EventTagRootAI() = default;

bool EventTagRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EventTagRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EventTagRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EventTagRootAI::loadParams_() {
    getMapUnitParam(&mLaunchEventByOnSignal_m, "LaunchEventByOnSignal");
    getMapUnitParam(&mLaunchEventByOffSignal_m, "LaunchEventByOffSignal");
    getMapUnitParam(&mIsEndlessEvent_m, "IsEndlessEvent");
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

}  // namespace uking::ai
