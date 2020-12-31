#include "Game/AI/AI/aiSwarmStopTimerEscape.h"

namespace uking::ai {

SwarmStopTimerEscape::SwarmStopTimerEscape(const InitArg& arg) : SwarmEscapeDie(arg) {}

SwarmStopTimerEscape::~SwarmStopTimerEscape() = default;

bool SwarmStopTimerEscape::init_(sead::Heap* heap) {
    return SwarmEscapeDie::init_(heap);
}

void SwarmStopTimerEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmEscapeDie::enter_(params);
}

void SwarmStopTimerEscape::leave_() {
    SwarmEscapeDie::leave_();
}

void SwarmStopTimerEscape::loadParams_() {
    SwarmEscapeDie::loadParams_();
    getStaticParam(&mStopActorName_s, "StopActorName");
}

}  // namespace uking::ai
