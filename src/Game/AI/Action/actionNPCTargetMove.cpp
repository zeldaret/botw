#include "Game/AI/Action/actionNPCTargetMove.h"

namespace uking::action {

NPCTargetMove::NPCTargetMove(const InitArg& arg) : RandomMoveAction(arg) {}

NPCTargetMove::~NPCTargetMove() = default;

bool NPCTargetMove::init_(sead::Heap* heap) {
    return RandomMoveAction::init_(heap);
}

void NPCTargetMove::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void NPCTargetMove::leave_() {
    RandomMoveAction::leave_();
}

void NPCTargetMove::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mUpdateTargetPosInterval_s, "UpdateTargetPosInterval");
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mStopTime_s, "StopTime");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mRunGoalDistance_s, "RunGoalDistance");
    getStaticParam(&mDistOnFailure_s, "DistOnFailure");
    getStaticParam(&mIsPathOptimization_s, "IsPathOptimization");
    getStaticParam(&mIsShelterFromRain_s, "IsShelterFromRain");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NPCTargetMove::calc_() {
    RandomMoveAction::calc_();
}

}  // namespace uking::action
