#include "Game/AI/Action/actionGuardianMiniGuardBreak.h"

namespace uking::action {

GuardianMiniGuardBreak::GuardianMiniGuardBreak(const InitArg& arg) : GuardBreak(arg) {}

GuardianMiniGuardBreak::~GuardianMiniGuardBreak() = default;

void GuardianMiniGuardBreak::loadParams_() {
    GuardBreak::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mGuardBreakASName_s, "GuardBreakASName");
    getStaticParam(&mOtherASName_s, "OtherASName");
}

}  // namespace uking::action
