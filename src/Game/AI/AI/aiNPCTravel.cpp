#include "Game/AI/AI/aiNPCTravel.h"

namespace uking::ai {

NPCTravel::NPCTravel(const InitArg& arg) : NPCTravelBase(arg) {}

NPCTravel::~NPCTravel() = default;

bool NPCTravel::init_(sead::Heap* heap) {
    return NPCTravelBase::init_(heap);
}

void NPCTravel::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCTravelBase::enter_(params);
}

void NPCTravel::leave_() {
    NPCTravelBase::leave_();
}

void NPCTravel::loadParams_() {
    NPCTravelBase::loadParams_();
    getStaticParam(&mWaitHorseReturnDist_s, "WaitHorseReturnDist");
    getStaticParam(&mGiveUpWaitHorseTime_s, "GiveUpWaitHorseTime");
}

}  // namespace uking::ai
