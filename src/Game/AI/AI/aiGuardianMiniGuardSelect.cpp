#include "Game/AI/AI/aiGuardianMiniGuardSelect.h"

namespace uking::ai {

GuardianMiniGuardSelect::GuardianMiniGuardSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniGuardSelect::~GuardianMiniGuardSelect() = default;

void GuardianMiniGuardSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniGuardSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniGuardSelect::loadParams_() {
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
}

}  // namespace uking::ai
