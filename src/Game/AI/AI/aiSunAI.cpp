#include "Game/AI/AI/aiSunAI.h"

namespace uking::ai {

SunAI::SunAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool SunAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SunAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SunAI::loadParams_() {}

}  // namespace uking::ai
