#include "Game/AI/AI/aiNPCTalkBalloon.h"

namespace uking::ai {

NPCTalkBalloon::NPCTalkBalloon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCTalkBalloon::~NPCTalkBalloon() = default;

void NPCTalkBalloon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCTalkBalloon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCTalkBalloon::loadParams_() {
    getStaticParam(&mDurationTime_s, "DurationTime");
    getStaticParam(&mDelayFrame_s, "DelayFrame");
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
