#include "Game/AI/AI/aiHorseRiddenAI.h"

namespace uking::ai {

HorseRiddenAI::HorseRiddenAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool HorseRiddenAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRiddenAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRiddenAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRiddenAI::loadParams_() {}

}  // namespace uking::ai
