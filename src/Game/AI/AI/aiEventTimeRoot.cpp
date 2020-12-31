#include "Game/AI/AI/aiEventTimeRoot.h"

namespace uking::ai {

EventTimeRoot::EventTimeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EventTimeRoot::~EventTimeRoot() = default;

bool EventTimeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EventTimeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EventTimeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EventTimeRoot::loadParams_() {
    getStaticParam(&mTimeLimit_s, "TimeLimit");
    getStaticParam(&mIsCountDown_s, "IsCountDown");
}

}  // namespace uking::ai
