#include "Game/AI/Action/actionGuardianMiniGuardBattleWalk.h"

namespace uking::action {

GuardianMiniGuardBattleWalk::GuardianMiniGuardBattleWalk(const InitArg& arg)
    : BattleCloseWalk(arg) {}

GuardianMiniGuardBattleWalk::~GuardianMiniGuardBattleWalk() = default;

bool GuardianMiniGuardBattleWalk::init_(sead::Heap* heap) {
    return BattleCloseWalk::init_(heap);
}

void GuardianMiniGuardBattleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseWalk::enter_(params);
}

void GuardianMiniGuardBattleWalk::leave_() {
    BattleCloseWalk::leave_();
}

void GuardianMiniGuardBattleWalk::loadParams_() {
    BattleCloseWalk::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianMiniGuardBattleWalk::calc_() {
    BattleCloseWalk::calc_();
}

}  // namespace uking::action
