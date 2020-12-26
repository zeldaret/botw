#include "Game/AI/Action/actionGuardianMiniGuardTurn.h"

namespace uking::action {

GuardianMiniGuardTurn::GuardianMiniGuardTurn(const InitArg& arg) : Turn(arg) {}

GuardianMiniGuardTurn::~GuardianMiniGuardTurn() = default;

bool GuardianMiniGuardTurn::init_(sead::Heap* heap) {
    return Turn::init_(heap);
}

void GuardianMiniGuardTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    Turn::enter_(params);
}

void GuardianMiniGuardTurn::leave_() {
    Turn::leave_();
}

void GuardianMiniGuardTurn::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianMiniGuardTurn::calc_() {
    Turn::calc_();
}

}  // namespace uking::action
