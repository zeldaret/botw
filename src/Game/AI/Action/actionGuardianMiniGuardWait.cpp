#include "Game/AI/Action/actionGuardianMiniGuardWait.h"

namespace uking::action {

GuardianMiniGuardWait::GuardianMiniGuardWait(const InitArg& arg) : GuardianMiniWait(arg) {}

GuardianMiniGuardWait::~GuardianMiniGuardWait() = default;

bool GuardianMiniGuardWait::init_(sead::Heap* heap) {
    return GuardianMiniWait::init_(heap);
}

void GuardianMiniGuardWait::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMiniWait::enter_(params);
}

void GuardianMiniGuardWait::leave_() {
    GuardianMiniWait::leave_();
}

void GuardianMiniGuardWait::loadParams_() {
    GuardianMiniWait::loadParams_();
    getStaticParam(&mGuardASName_s, "GuardASName");
}

void GuardianMiniGuardWait::calc_() {
    GuardianMiniWait::calc_();
}

}  // namespace uking::action
