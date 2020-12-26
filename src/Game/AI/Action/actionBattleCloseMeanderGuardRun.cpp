#include "Game/AI/Action/actionBattleCloseMeanderGuardRun.h"

namespace uking::action {

BattleCloseMeanderGuardRun::BattleCloseMeanderGuardRun(const InitArg& arg)
    : BattleCloseMeanderRun(arg) {}

BattleCloseMeanderGuardRun::~BattleCloseMeanderGuardRun() = default;

bool BattleCloseMeanderGuardRun::init_(sead::Heap* heap) {
    return BattleCloseMeanderRun::init_(heap);
}

void BattleCloseMeanderGuardRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMeanderRun::enter_(params);
}

void BattleCloseMeanderGuardRun::leave_() {
    BattleCloseMeanderRun::leave_();
}

void BattleCloseMeanderGuardRun::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
    getStaticParam(&mMeanderWidth_s, "MeanderWidth");
    getStaticParam(&mMeanderSpeed_s, "MeanderSpeed");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
}

void BattleCloseMeanderGuardRun::calc_() {
    BattleCloseMeanderRun::calc_();
}

}  // namespace uking::action
