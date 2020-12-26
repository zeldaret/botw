#include "Game/AI/Action/actionGuardianMiniGuardSideWalk.h"

namespace uking::action {

GuardianMiniGuardSideWalk::GuardianMiniGuardSideWalk(const InitArg& arg) : TargetCircleWalk(arg) {}

GuardianMiniGuardSideWalk::~GuardianMiniGuardSideWalk() = default;

bool GuardianMiniGuardSideWalk::init_(sead::Heap* heap) {
    return TargetCircleWalk::init_(heap);
}

void GuardianMiniGuardSideWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetCircleWalk::enter_(params);
}

void GuardianMiniGuardSideWalk::leave_() {
    TargetCircleWalk::leave_();
}

void GuardianMiniGuardSideWalk::loadParams_() {
    TargetCircleWalk::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianMiniGuardSideWalk::calc_() {
    TargetCircleWalk::calc_();
}

}  // namespace uking::action
