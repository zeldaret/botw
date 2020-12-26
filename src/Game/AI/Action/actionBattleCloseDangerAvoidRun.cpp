#include "Game/AI/Action/actionBattleCloseDangerAvoidRun.h"

namespace uking::action {

BattleCloseDangerAvoidRun::BattleCloseDangerAvoidRun(const InitArg& arg)
    : BattleCloseExplosivesAvoidRun(arg) {}

BattleCloseDangerAvoidRun::~BattleCloseDangerAvoidRun() = default;

bool BattleCloseDangerAvoidRun::init_(sead::Heap* heap) {
    return BattleCloseExplosivesAvoidRun::init_(heap);
}

void BattleCloseDangerAvoidRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseExplosivesAvoidRun::enter_(params);
}

void BattleCloseDangerAvoidRun::leave_() {
    BattleCloseExplosivesAvoidRun::leave_();
}

void BattleCloseDangerAvoidRun::loadParams_() {
    BattleCloseExplosivesAvoidRun::loadParams_();
    getStaticParam(&mAvoidSubAngle_s, "AvoidSubAngle");
}

void BattleCloseDangerAvoidRun::calc_() {
    BattleCloseExplosivesAvoidRun::calc_();
}

}  // namespace uking::action
