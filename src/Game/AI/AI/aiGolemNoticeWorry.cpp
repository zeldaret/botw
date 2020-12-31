#include "Game/AI/AI/aiGolemNoticeWorry.h"

namespace uking::ai {

GolemNoticeWorry::GolemNoticeWorry(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemNoticeWorry::~GolemNoticeWorry() = default;

bool GolemNoticeWorry::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemNoticeWorry::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemNoticeWorry::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemNoticeWorry::loadParams_() {
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
