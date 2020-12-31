#include "Game/AI/AI/aiJustAvoidFinishWait.h"

namespace uking::ai {

JustAvoidFinishWait::JustAvoidFinishWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

JustAvoidFinishWait::~JustAvoidFinishWait() = default;

bool JustAvoidFinishWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void JustAvoidFinishWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void JustAvoidFinishWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void JustAvoidFinishWait::loadParams_() {
    getStaticParam(&mIsUseWaitAfterMain_s, "IsUseWaitAfterMain");
}

}  // namespace uking::ai
