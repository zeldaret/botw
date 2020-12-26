#include "Game/AI/Action/actionGuardianMiniGuardBreak.h"

namespace uking::action {

GuardianMiniGuardBreak::GuardianMiniGuardBreak(const InitArg& arg) : GuardBreak(arg) {}

GuardianMiniGuardBreak::~GuardianMiniGuardBreak() = default;

bool GuardianMiniGuardBreak::init_(sead::Heap* heap) {
    return GuardBreak::init_(heap);
}

void GuardianMiniGuardBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardBreak::enter_(params);
}

void GuardianMiniGuardBreak::leave_() {
    GuardBreak::leave_();
}

void GuardianMiniGuardBreak::loadParams_() {
    GuardBreak::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mGuardBreakASName_s, "GuardBreakASName");
    getStaticParam(&mOtherASName_s, "OtherASName");
}

void GuardianMiniGuardBreak::calc_() {
    GuardBreak::calc_();
}

}  // namespace uking::action
