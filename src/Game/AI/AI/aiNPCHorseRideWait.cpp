#include "Game/AI/AI/aiNPCHorseRideWait.h"

namespace uking::ai {

NPCHorseRideWait::NPCHorseRideWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCHorseRideWait::~NPCHorseRideWait() = default;

bool NPCHorseRideWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCHorseRideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCHorseRideWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCHorseRideWait::loadParams_() {}

}  // namespace uking::ai
