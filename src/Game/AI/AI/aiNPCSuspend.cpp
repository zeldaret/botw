#include "Game/AI/AI/aiNPCSuspend.h"

namespace uking::ai {

NPCSuspend::NPCSuspend(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCSuspend::~NPCSuspend() = default;

bool NPCSuspend::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCSuspend::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCSuspend::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCSuspend::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mEndMoveTime_s, "EndMoveTime");
    getStaticParam(&mRetryCount_s, "RetryCount");
    getStaticParam(&mSearchRadius_s, "SearchRadius");
    getDynamicParam(&mASName_d, "ASName");
}

}  // namespace uking::ai
