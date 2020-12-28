#include "Game/AI/Action/actionGuardianMiniGuardSideWalk.h"

namespace uking::action {

GuardianMiniGuardSideWalk::GuardianMiniGuardSideWalk(const InitArg& arg) : TargetCircleWalk(arg) {}

GuardianMiniGuardSideWalk::~GuardianMiniGuardSideWalk() = default;

void GuardianMiniGuardSideWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetCircleWalk::enter_(params);
}

void GuardianMiniGuardSideWalk::loadParams_() {
    TargetCircleWalk::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
