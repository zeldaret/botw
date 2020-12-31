#include "Game/AI/AI/aiStopTimerObserver.h"

namespace uking::ai {

StopTimerObserver::StopTimerObserver(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StopTimerObserver::~StopTimerObserver() = default;

bool StopTimerObserver::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StopTimerObserver::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StopTimerObserver::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StopTimerObserver::loadParams_() {}

}  // namespace uking::ai
