#include "Game/AI/AI/aiMoonAI.h"

namespace uking::ai {

MoonAI::MoonAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool MoonAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoonAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoonAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoonAI::loadParams_() {}

}  // namespace uking::ai
