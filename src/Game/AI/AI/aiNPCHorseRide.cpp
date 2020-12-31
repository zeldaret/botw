#include "Game/AI/AI/aiNPCHorseRide.h"

namespace uking::ai {

NPCHorseRide::NPCHorseRide(const InitArg& arg) : NonPlayerHorseRide(arg) {}

NPCHorseRide::~NPCHorseRide() = default;

bool NPCHorseRide::init_(sead::Heap* heap) {
    return NonPlayerHorseRide::init_(heap);
}

void NPCHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    NonPlayerHorseRide::enter_(params);
}

void NPCHorseRide::leave_() {
    NonPlayerHorseRide::leave_();
}

void NPCHorseRide::loadParams_() {
    getStaticParam(&mGearLevel_s, "GearLevel");
    getStaticParam(&mGearResetPathNum_s, "GearResetPathNum");
    getStaticParam(&mPlayerNearDistance_s, "PlayerNearDistance");
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

}  // namespace uking::ai
