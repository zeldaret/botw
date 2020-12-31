#include "Game/AI/AI/aiSwitchLinkTagCheck.h"

namespace uking::ai {

SwitchLinkTagCheck::SwitchLinkTagCheck(const InitArg& arg) : SwitchAI(arg) {}

SwitchLinkTagCheck::~SwitchLinkTagCheck() = default;

bool SwitchLinkTagCheck::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchLinkTagCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
}

void SwitchLinkTagCheck::leave_() {
    SwitchAI::leave_();
}

void SwitchLinkTagCheck::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mSignalType_s, "SignalType");
    getStaticParam(&mSetEnableJobTimerTiming_s, "SetEnableJobTimerTiming");
}

}  // namespace uking::ai
