#include "Game/AI/Action/actionGuardWithAS.h"

namespace uking::action {

GuardWithAS::GuardWithAS(const InitArg& arg) : Guard(arg) {}

GuardWithAS::~GuardWithAS() = default;

void GuardWithAS::loadParams_() {
    Guard::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
