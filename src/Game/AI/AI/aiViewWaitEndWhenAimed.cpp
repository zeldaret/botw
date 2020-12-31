#include "Game/AI/AI/aiViewWaitEndWhenAimed.h"

namespace uking::ai {

ViewWaitEndWhenAimed::ViewWaitEndWhenAimed(const InitArg& arg) : TimeredViewWait(arg) {}

ViewWaitEndWhenAimed::~ViewWaitEndWhenAimed() = default;

bool ViewWaitEndWhenAimed::init_(sead::Heap* heap) {
    return TimeredViewWait::init_(heap);
}

void ViewWaitEndWhenAimed::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredViewWait::enter_(params);
}

void ViewWaitEndWhenAimed::leave_() {
    TimeredViewWait::leave_();
}

void ViewWaitEndWhenAimed::loadParams_() {
    TimeredViewWait::loadParams_();
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mAimedAngle_s, "AimedAngle");
    getStaticParam(&mBowRange_s, "BowRange");
    getStaticParam(&mBoneName_s, "BoneName");
}

}  // namespace uking::ai
