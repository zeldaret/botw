#include "Game/Actor/AI/aiNPCHorseRide.h"

namespace uking::ai {

NPCHorseRide::NPCHorseRide(const InitArg& arg) : RideHorseNonPlayer(arg) {}

NPCHorseRide::~NPCHorseRide() = default;

bool NPCHorseRide::init_(sead::Heap* heap) {
    return RideHorseNonPlayer::init_(heap);
}

void NPCHorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    RideHorseNonPlayer::enter_(params);
}

void NPCHorseRide::leave_() {
    RideHorseNonPlayer::leave_();
}

void NPCHorseRide::loadParams_() {
    getStaticParam(&mGearLevel_s, "GearLevel");
    getStaticParam(&mGearResetPathNum_s, "GearResetPathNum");
    getStaticParam(&mPlayerNearDistance_s, "PlayerNearDistance");
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

}  // namespace uking::ai
