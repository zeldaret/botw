#include "Game/AI/Action/actionBattleCloseMeanderRun.h"

namespace uking::action {

BattleCloseMeanderRun::BattleCloseMeanderRun(const InitArg& arg) : BattleCloseMoveAction(arg) {}

BattleCloseMeanderRun::~BattleCloseMeanderRun() = default;

void BattleCloseMeanderRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
}

void BattleCloseMeanderRun::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
    getStaticParam(&mMeanderWidth_s, "MeanderWidth");
    getStaticParam(&mMeanderSpeed_s, "MeanderSpeed");
    getStaticParam(&mJumpUpSpeedReduceRatio_s, "JumpUpSpeedReduceRatio");
}

void BattleCloseMeanderRun::calc_() {
    BattleCloseMoveAction::calc_();
}

}  // namespace uking::action
