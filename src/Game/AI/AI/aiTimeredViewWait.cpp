#include "Game/AI/AI/aiTimeredViewWait.h"

namespace uking::ai {

TimeredViewWait::TimeredViewWait(const InitArg& arg) : ViewWait(arg) {}

TimeredViewWait::~TimeredViewWait() = default;

bool TimeredViewWait::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void TimeredViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void TimeredViewWait::leave_() {
    ViewWait::leave_();
}

void TimeredViewWait::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

}  // namespace uking::ai
