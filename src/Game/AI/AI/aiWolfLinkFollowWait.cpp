#include "Game/AI/AI/aiWolfLinkFollowWait.h"

namespace uking::ai {

WolfLinkFollowWait::WolfLinkFollowWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkFollowWait::~WolfLinkFollowWait() = default;

bool WolfLinkFollowWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkFollowWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkFollowWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkFollowWait::loadParams_() {
    getStaticParam(&mTurnThreshold_s, "TurnThreshold");
    getStaticParam(&mLockonTurnThreshold_s, "LockonTurnThreshold");
}

}  // namespace uking::ai
