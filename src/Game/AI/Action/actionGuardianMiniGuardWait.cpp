#include "Game/AI/Action/actionGuardianMiniGuardWait.h"

namespace uking::action {

GuardianMiniGuardWait::GuardianMiniGuardWait(const InitArg& arg) : GuardianMiniWait(arg) {}

GuardianMiniGuardWait::~GuardianMiniGuardWait() = default;

void GuardianMiniGuardWait::loadParams_() {
    GuardianMiniWait::loadParams_();
    getStaticParam(&mGuardASName_s, "GuardASName");
}

}  // namespace uking::action
