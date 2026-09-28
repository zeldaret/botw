#include "Game/Actor/AI/aiNPCWander.h"

namespace uking::ai {

NPCWander::NPCWander(const InitArg& arg) : NPCScheduleMove(arg) {}

NPCWander::~NPCWander() = default;

bool NPCWander::init_(sead::Heap* heap) {
    return NPCScheduleMove::init_(heap);
}

void NPCWander::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCScheduleMove::enter_(params);
}

void NPCWander::leave_() {
    NPCScheduleMove::leave_();
}

void NPCWander::loadParams_() {
    NPCScheduleMove::loadParams_();
    getStaticParam(&mRainWaitTime_s, "RainWaitTime");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mRailUpdateDistRate_s, "RailUpdateDistRate");
    getStaticParam(&mRainDestination_s, "RainDestination");
    getStaticParam(&mNormalASKeyName_s, "NormalASKeyName");
    getStaticParam(&mRainASKeyName_s, "RainASKeyName");
    getStaticParam(&mRailUniqueName_s, "RailUniqueName");
    getDynamicParam(&mIsPathRest_d, "IsPathRest");
}

}  // namespace uking::ai
