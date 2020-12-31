#include "Game/AI/AI/aiLinkTagCheck.h"

namespace uking::ai {

LinkTagCheck::LinkTagCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool LinkTagCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LinkTagCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LinkTagCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LinkTagCheck::loadParams_() {
    getStaticParam(&mSignalType_s, "SignalType");
    getStaticParam(&mSetEnableJobTimerTiming_s, "SetEnableJobTimerTiming");
    getStaticParam(&mIsNotConnectOn_s, "IsNotConnectOn");
    getStaticParam(&mIsCheckChildEnd_s, "IsCheckChildEnd");
}

}  // namespace uking::ai
