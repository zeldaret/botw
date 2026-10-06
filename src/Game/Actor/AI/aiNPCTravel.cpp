#include "Game/Actor/AI/aiNPCTravel.h"

namespace uking::ai {

NPCTravel::NPCTravel(const InitArg& arg) : NPCScheduleMove(arg) {}

NPCTravel::~NPCTravel() = default;

bool NPCTravel::init_(sead::Heap* heap) {
    return NPCScheduleMove::init_(heap);
}

void NPCTravel::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCScheduleMove::enter_(params);
}

void NPCTravel::leave_() {
    NPCScheduleMove::leave_();
}

void NPCTravel::loadParams_() {
    NPCScheduleMove::loadParams_();
    getStaticParam(&mWaitHorseReturnDist_s, "WaitHorseReturnDist");
    getStaticParam(&mGiveUpWaitHorseTime_s, "GiveUpWaitHorseTime");
}

}  // namespace uking::ai
