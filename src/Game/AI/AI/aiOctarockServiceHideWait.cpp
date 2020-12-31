#include "Game/AI/AI/aiOctarockServiceHideWait.h"

namespace uking::ai {

OctarockServiceHideWait::OctarockServiceHideWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OctarockServiceHideWait::~OctarockServiceHideWait() = default;

bool OctarockServiceHideWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OctarockServiceHideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OctarockServiceHideWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OctarockServiceHideWait::loadParams_() {
    getStaticParam(&mSafeAreaDist_s, "SafeAreaDist");
    getStaticParam(&mSafeAreaDistRange_s, "SafeAreaDistRange");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
    getStaticParam(&mMinWaitTimeRand_s, "MinWaitTimeRand");
    getStaticParam(&mNoticeTerrorLevel_s, "NoticeTerrorLevel");
    getStaticParam(&mNoticeWorryRange_s, "NoticeWorryRange");
}

}  // namespace uking::ai
