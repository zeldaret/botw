#include "Game/AI/Action/actionGuardianMiniGuardBattleWalk.h"

namespace uking::action {

GuardianMiniGuardBattleWalk::GuardianMiniGuardBattleWalk(const InitArg& arg)
    : BattleCloseWalk(arg) {}

GuardianMiniGuardBattleWalk::~GuardianMiniGuardBattleWalk() = default;

void GuardianMiniGuardBattleWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseWalk::enter_(params);
}

void GuardianMiniGuardBattleWalk::loadParams_() {
    BattleCloseWalk::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
